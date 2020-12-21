#include "../include/iml_interpreter.h"
#include "../include/iml_factory.h"
#include "../include/iml_tag.h"

#include <stdexcept>

// =============================================== // SELECTORS AND ITERATORS // =============================================== //

void iml_interpreter::next()
{
    ++t_list_iterator;
}

void iml_interpreter::previous()
{
    --t_list_iterator;
}

iml_token iml_interpreter::current()
{
    return *t_list_iterator;
}

// ================================================================================================================== //

// =============================================== // PREDICATES // =============================================== //

bool iml_interpreter::end_expression()
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

bool iml_interpreter::is_value()
{
    return current().type == iml_token_type::number || current().type == iml_token_type::string;
}

bool iml_interpreter::is_body_expression()
{
    return hierarchy.top()->type() == iml_tag_type::let;
}


// ================================================================================================================== //

// =============================================== // ATOM PARSING // =============================================== //

void iml_interpreter::parse_token(iml_token_type type)
{
    if (current().type != type)
    {
        switch (type)
        {
            case iml_token_type::open_bracket: 
                throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
            
            case iml_token_type::close_bracket: 
                throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
            
            case iml_token_type::slash: 
                throw std::logic_error("Expected slash character '/', given " + current().text + " !");
            
            case iml_token_type::quote: 
                throw std::logic_error("Expected quote character '\"', given " + current().text + " !"); 
            
            case iml_token_type::string: 
                throw std::logic_error("Expected string, given " + current().text + " !");
        }
    }
    next();
}

void iml_interpreter::parse_open_tag()
{
    parse_token(iml_token_type::open_bracket);

    std::string tag_type = current().text;
    if(!iml_factory::exists(tag_type))
    {
        throw std::invalid_argument
            (
                "Tag " 
                + current().text 
                + 
                " does not exist!"
            );
    }

    parse_token(iml_token_type::string);

    if (current().type == iml_token_type::quote) 
    {
        hierarchy.push(iml_factory::to_atag(tag_type, parse_attribute()));
    }
    else
    {
        hierarchy.push(iml_factory::to_tag(tag_type));
    }
    
    parse_token(iml_token_type::close_bracket);
}

void iml_interpreter::parse_body_tag()
{
    parse_token(iml_token_type::open_bracket);

    if (current().text != "BODY") 
    {
        throw std::logic_error
            (
                "Expected string \"BODY\", given " 
                + current().text 
                + " ! Missing or invalid BODY tag syntax!"
            );
    }
    next();

    parse_token(iml_token_type::slash);
    parse_token(iml_token_type::close_bracket);
}

void iml_interpreter::parse_close_tag()
{
    parse_token(iml_token_type::open_bracket);
    parse_token(iml_token_type::slash);

    std::string tag_type = current().text;
    if (hierarchy.top()->type() != iml_factory::to_type(tag_type)) 
    {
        throw std::logic_error
            (
                "Invalid close tag type, expected " 
                + iml_factory::to_string(hierarchy.top()->type()) 
                + " , given " 
                + current().text 
                + " !"
            );
    }

    parse_token(iml_token_type::string);
    parse_token(iml_token_type::close_bracket);
}

iml_attribute iml_interpreter::parse_attribute()
{
    parse_token(iml_token_type::quote);

    if (!is_value()) 
    {
        throw std::invalid_argument
            (
                "Attribute expects value argument!"
            );
    }
    std::string attribute_text = current().text;
    next();

    parse_token(iml_token_type::quote);
    
    return iml_attribute(attribute_text);
}

// ================================================================================================================== //

// =============================================== // EXPRESSION EVALUATING // =============================================== //

void iml_interpreter::evaluate_value()
{
    if (current().type == iml_token_type::string) 
    {
        if (linked_names.find(current().text) == linked_names.end()) 
        {
            throw std::invalid_argument
                (
                    current().text 
                    + " is not defined!"
                );
        }
        hierarchy.top()->add(linked_names[current().text].top());
    }
    else
    {
        hierarchy.top()->add(stod(current().text));
    }
    next();
}

void iml_interpreter::evaluate_expression()
{
    if (end_expression())
    {
        return;
    }
    else if (is_value())
    {
        evaluate_value();
    }
    else
    {
        evaluate_tag_expression();
    } 
    evaluate_expression();
}

void iml_interpreter::evaluate_tag_expression()
{
    parse_open_tag();
    evaluate_expression();

    if (is_body_expression())
    {
        evaluate_body_expression();
    }
    parse_close_tag();

    std::list<double> values = hierarchy.top()->evaluate();
    hierarchy.pop();
    hierarchy.top()->add(values);
}

void iml_interpreter::evaluate_body_expression()
{
    parse_body_tag();

    std::string attribute_id = hierarchy.top()->attribute().text();
    linked_names[attribute_id].push(hierarchy.top()->evaluate());
    hierarchy.top()->clear();

    evaluate_expression();

    linked_names[attribute_id].pop();
    if (linked_names[attribute_id].empty())
    {
        linked_names.erase(attribute_id);
    }
}

// ================================================================================================================== //

void iml_interpreter::build(std::istream& in, std::ostream& out)
{
    try
    {
        hierarchy.push(new iml_tag<iml_tag_type::iml_root>());
        t_list = iml_tokenizer(in).tokenize();
        t_list_iterator = t_list.begin();

        evaluate_expression();
        
        out << "Evaluation complete:\n";
        std::list<double> end_result = hierarchy.top()->evaluate();
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