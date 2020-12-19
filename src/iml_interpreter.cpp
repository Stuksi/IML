#include "../include/iml_interpreter.h"
#include "../include/iml_factory.h"
#include "../include/iml_root_tag.h"

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

// ================================================================================================================== //

// =============================================== // ATOM PARSING // =============================================== //

void iml_interpreter::evaluate_token(iml_token_type type)
{
    if (current().type != type)
    {
        switch (type)
        {
        case iml_token_type::open_bracket: throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
        case iml_token_type::close_bracket: throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
        case iml_token_type::slash: throw std::logic_error("Expected slash character '/', given " + current().text + " !");
        case iml_token_type::quote: throw std::logic_error("Expected quote character '\"', given " + current().text + " !"); 
        case iml_token_type::string: throw std::logic_error("Expected string, given " + current().text + " !");
        }
    }
    if (type == iml_token_type::string)
    {
        return; 
    }
    next();
}

void iml_interpreter::evaluate_value()
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

void iml_interpreter::evaluate_open_tag()
{
    evaluate_token(iml_token_type::open_bracket);
    evaluate_token(iml_token_type::string);
    hierarchy.push(iml_factory::stotag(current().text));
    next();
    if (current().type == iml_token_type::quote)
    {
        evaluate_attribute();
    }
    else 
    {
        try
        {
            hierarchy.top()->get_attribute();
            throw std::logic_error("Tag expects an attribute in definition!");
        }
        catch (const std::logic_error& e)
        {
            if (!std::string("Tag expects an attribute in definition!").compare(e.what()))
            {
                throw e;
            }
        }
    }
    evaluate_token(iml_token_type::close_bracket);
}

void iml_interpreter::evaluate_body_tag()
{
    evaluate_token(iml_token_type::open_bracket);
    if (current().text != "BODY") 
    {
        throw std::logic_error("Expected string \"BODY\", given " + current().text + " ! Missing or invalid BODY tag syntax!");
    }
    next();
    evaluate_token(iml_token_type::slash);
    evaluate_token(iml_token_type::close_bracket);
}

void iml_interpreter::evaluate_close_tag()
{
    evaluate_token(iml_token_type::open_bracket);
    evaluate_token(iml_token_type::slash);
    evaluate_token(iml_token_type::string);
    if (hierarchy.top()->type() != iml_factory::stotype(current().text)) 
    {
        throw std::logic_error("Invalid close tag type, expected " + iml_factory::typetos(hierarchy.top()->type()) + " , given " + current().text + " !");
    }
    next();
    evaluate_token(iml_token_type::close_bracket);
}

void iml_interpreter::evaluate_attribute()
{
    evaluate_token(iml_token_type::quote);
    if (!is_value()) 
    {
        throw std::invalid_argument("Attribute expects value argument!");
    }
    hierarchy.top()->set_attribute(iml_attribute(current().text));
    next();
    evaluate_token(iml_token_type::quote);
}

// ================================================================================================================== //

// =============================================== // EXPRESSION PARSING // =============================================== //

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
    evaluate_open_tag();
    evaluate_expression();
    if (hierarchy.top()->type() == iml_tag_type::let)
    {
        evaluate_let_tag_expression();
    }
    evaluate_close_tag();

    // Add the current tag evaluation to the previous in the hierarchy.
    std::list<double> values = hierarchy.top()->eval();
    hierarchy.pop();
    hierarchy.top()->add_values(values);
}

void iml_interpreter::evaluate_let_tag_expression()
{
    evaluate_body_tag();

    // Connect the attribute name whit the current values list.
    std::string attribute_id = hierarchy.top()->get_attribute().get();
    linked_names[attribute_id].push(hierarchy.top()->eval());
    hierarchy.top()->set_values({});

    evaluate_expression();

    // Remove the last added connection and if there are no more 
    // connections whit the current name, delete the connection.
    linked_names[attribute_id].pop();
    if (linked_names[attribute_id].empty())
    {
        linked_names.erase(attribute_id);
    }
}

// ================================================================================================================== //

void iml_interpreter::build(std::istream& in, std::ostream& out)
{
    hierarchy.push(new iml_root_tag());

    try
    {
        t_list = iml_tokenizer(in).tokenize();
        t_list_iterator = t_list.begin();

        evaluate_expression();
        
        out << "Evaluation complete:\n";
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