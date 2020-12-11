#include "../include/iml_parser.h"
#include "../include/iml_factory.h"
#include "../include/iml_root_tag.h"

#include <stdexcept>

void iml_parser::next()
{
    ++t_list_iterator;
}

void iml_parser::previous()
{
    --t_list_iterator;
}

iml_token iml_parser::current()
{
    return *t_list_iterator;
}

bool iml_parser::end_expression()
{
    if (current().type == iml_token_type::open_bracket)
    {
        next();
        if (current().type == iml_token_type::slash || current().text == "BODY")
        {
            previous();
            return true;
        }
        previous();
    }
    return t_list_iterator == t_list.end()
        || current().text == "end_of_file()";
}

bool iml_parser::is_value()
{
    return current().type == iml_token_type::number || current().type == iml_token_type::string;
}

void iml_parser::parse_open_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
    }
    next();
    if (current().type != iml_token_type::string) 
    {
        throw std::logic_error("Expected string, given " + current().text + " !");
    }
    iml_tag *new_tag = iml_factory::stotag(current().text);
    hierarchy.push(new_tag);
    next();
    if (current().type == iml_token_type::quote)
    {
        parse_attribute();
    }
    if (current().type != iml_token_type::close_bracket) 
    {
        throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
    }
    next();
}

void iml_parser::parse_body_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
    }
    next();
    if (current().text != "BODY") 
    {
        throw std::logic_error("Expected string \"BODY\", given " + current().text + " ! Missing or invalid BODY tag syntax!");
    }
    next();
    if (current().type != iml_token_type::slash) 
    {
        throw std::logic_error("Expected slash character '/', given " + current().text + " !");
    }
    next();
    if (current().type != iml_token_type::close_bracket) 
    {
        throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
    }
    next();
}

void iml_parser::parse_close_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
    }
    next();
    if (current().type != iml_token_type::slash) 
    {
        throw std::logic_error("Expected slash character '/', given " + current().text + " ! Missing close " + iml_factory::typetos(hierarchy.top()->type()) + " tag!");
    }
    next();
    if (current().type != iml_token_type::string) 
    {
        throw std::logic_error("Expected string, given " + current().text + " !");
    }
    if (hierarchy.top()->type() != iml_factory::stotype(current().text)) 
    {
        throw std::logic_error("Invalid close tag type, expected " + iml_factory::typetos(hierarchy.top()->type()) + " , given " + current().text + " !");
    }
    next();
    if (current().type != iml_token_type::close_bracket) 
    {
        throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
    }
    next();
}

void iml_parser::parse_attribute()
{
    if (current().type != iml_token_type::quote) 
    {
        throw std::logic_error("Expected quote character '\"', given " + current().text + " !");
    }
    next();
    if (!is_value()) 
    {
        throw std::invalid_argument("Attribute expects value argument!");
    }
    iml_attribute attribute;
    attribute.set(current().text);
    next();
    if (current().type != iml_token_type::quote) 
    {
        throw std::logic_error("Expected quote character '\"', given " + current().text + " !");
    }
    hierarchy.top()->set_attribute(attribute);
    next();
}

void iml_parser::parse_expression()
{
    if (end_expression())
    {
        return;
    } 
    else if (is_value())
    {
        parse_value_expression();
    }
    else 
    {
        parse_tag_expression();
    }
    parse_expression();
}

void iml_parser::parse_tag_expression()
{
    parse_open_tag();
    parse_expression();
    if (hierarchy.top()->type() == iml_tag_type::let)
    {
        parse_body_tag();
        std::string attribute_id = hierarchy.top()->get_attribute().get();
        linked_names[attribute_id].push(hierarchy.top()->eval());
        hierarchy.top()->set_values({});
        parse_expression();
        linked_names[attribute_id].pop();
        if (linked_names[attribute_id].empty())
        {
            linked_names.erase(attribute_id);
        }
    }
    parse_close_tag();

    std::list<double> values = hierarchy.top()->eval();
    hierarchy.pop();
    hierarchy.top()->add_values(values);
}

void iml_parser::parse_value_expression()
{
    if (current().type == iml_token_type::number)
    {
        hierarchy.top()->add_value(stod(current().text));
    }
    else 
    {   
        if (linked_names.find(current().text) == linked_names.end())
        {
            throw std::invalid_argument(current().text + " is not defined!");
        }
        hierarchy.top()->add_values(linked_names[current().text].top());
    }
    next();
}

void iml_parser::build(std::istream& in, std::ostream& out)
{

    hierarchy.push(new iml_root_tag());
    try
    {
        t_list = iml_tokenizer(in).tokenize();
        t_list_iterator = t_list.begin();
        parse_expression();
        std::list<double> end_result = hierarchy.top()->eval();
        for (auto i = end_result.begin(); i != --end_result.end(); ++i)
        {
            out << *i << " ";
        }
        if (end_result.size() > 0)
        {
            out << *(--end_result.end());
        }
    }
    catch(const std::runtime_error& e)
    {
        out << e.what();
    }
    catch(const std::invalid_argument& e)
    {
        out << "Invalid Argument at line " + std::to_string(current().position.row) + ", column " + std::to_string(current().position.col) + "! " + e.what();
    }
    catch(const std::logic_error& e)
    {
        out << "Logic Error at line " + std::to_string(current().position.row) + ", column " + std::to_string(current().position.col) + "! " + e.what();
    }
}