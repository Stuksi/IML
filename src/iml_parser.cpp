#include "../include/iml_parser.h"
#include "../include/iml_factory.h"
#include "../include/iml_root_tag.h"

iml_parser::iml_parser(std::istream& in) : t_list(iml_tokenizer(in).tokenize()), t_list_iterator(t_list.begin())
{}

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

bool iml_parser::more()
{
    return t_list_iterator != t_list.end();
}

bool iml_parser::is_value()
{
    return current().type == iml_token_type::number || current().type == iml_token_type::string;
}

bool iml_parser::is_end_tag()
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
    return false;
}

void iml_parser::parse_value()
{
    if (current().type == iml_token_type::number)
    {
        hierarchy.top()->add_value(stod(current().text));
    }
    else 
    {   
        hierarchy.top()->add_values(linked_names.get(current().text));
    }
    next();
}

void iml_parser::parse_open_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::string) 
    {
        throw;
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
        throw;
    }
    next();
}

void iml_parser::parse_body_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw;
    }
    next();
    if (current().text != "BODY") 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::slash) 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::close_bracket) 
    {
        throw;
    }
    next();
}

void iml_parser::parse_close_tag()
{
    if (current().type != iml_token_type::open_bracket) 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::slash) 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::string) 
    {
        throw;
    }
    if (hierarchy.top()->type() != iml_factory::stotype(current().text)) 
    {
        throw;
    }
    next();
    if (current().type != iml_token_type::close_bracket) 
    {
        throw;
    }
    next();
}

void iml_parser::parse_attribute()
{
    if (current().type != iml_token_type::quote) 
    {
        throw;
    }
    next();
    if (!is_value()) 
    {
        throw;
    }
    iml_attribute attribute;
    attribute.set(current().text);
    next();
    if (current().type != iml_token_type::quote) 
    {
        throw;
    }
    try
    {
        hierarchy.top()->set_attribute(attribute);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    next();
}

void iml_parser::parse_expression()
{
    if (!more() || is_end_tag())
    {
        return;
    } 
    else if (is_value())
    {
        parse_value();
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
        if (linked_names.contains(hierarchy.top()->get_attribute().get()))
        {
            throw;
        }
        linked_names.insert(hierarchy.top()->get_attribute().get(), hierarchy.top()->eval());
        hierarchy.top()->set_values(dllist<double>());
        parse_expression();
        linked_names.erase(hierarchy.top()->get_attribute().get());
    }
    parse_close_tag();

    dllist<double> values = hierarchy.top()->eval();
    hierarchy.pop();
    hierarchy.top()->add_values(values);
}

void iml_parser::build(std::ostream& out)
{
    hierarchy.push(new iml_root_tag());
    try
    {
        parse_expression();
        if (hierarchy.size() != 1)
        {
            throw;
        }
        out << hierarchy.top()->eval();
    }
    catch(const std::exception& e)
    {
        out << e.what();
    }
}