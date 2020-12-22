#include "../include/iml core headers/iml_interpreter.h"
#include "../include/iml tag headers/iml_tag_factory.h"
#include "../include/iml tag headers/iml_tag.h"
#include "../include/iml tag headers/iml_tag_type_converter.h"
#include <stdexcept>

bool iml_interpreter::is_body_expression()
{
    return hierarchy_.top()->type() == iml_tag_type::let;
}

void iml_interpreter::evaluate_expression()
{
    if (parser_->is_end())
    {
        return;
    }
    else if (parser_->is_value())
    {
        evaluate_value();
    }
    else
    {
        evaluate_tag_expression();
    } 
    evaluate_expression();
}

void iml_interpreter::evaluate_value()
{
    hierarchy_.top()->add(parser_->parse_value(links_));
}

void iml_interpreter::evaluate_tag_expression()
{
    hierarchy_.push(parser_->parse_open_tag());
    evaluate_expression();

    if (is_body_expression())
    {
        evaluate_body_expression();
    }

    tag close_tag = parser_->parse_close_tag();
    if (hierarchy_.top()->type() != close_tag->type())
    {
        throw std::logic_error
            (
                "Invalid close tag type, expected " 
                + iml_tag_type_converter::types[(int)hierarchy_.top()->type()]
                + " , given " 
                + iml_tag_type_converter::types[(int)close_tag->type()]
                + " !"
            );
    }

    std::list<double> values = hierarchy_.top()->evaluate();
    hierarchy_.pop();
    hierarchy_.top()->add(values);
}

void iml_interpreter::evaluate_body_expression()
{
    parser_->parse_body_tag();

    std::string name = hierarchy_.top()->attribute().text();
    links_[name].push(hierarchy_.top()->evaluate());
    hierarchy_.top()->clear();

    evaluate_expression();

    links_[name].pop();
    if (links_[name].empty())
    {
        links_.erase(name);
    }
}

std::list<double> iml_interpreter::evaluate(std::istream& in)
{
    try
    {
        parser_ = new iml_parser(in);
        hierarchy_.push(new iml_tag<iml_tag_type::root>());
        evaluate_expression();
        return hierarchy_.top()->evaluate();
    }
    catch(const std::runtime_error& e)
    {
        throw std::runtime_error(e.what());
    }
    catch(const std::invalid_argument& e)
    {
        throw std::invalid_argument("Invalid Argument at line " + std::to_string(parser_->cursor_position().row) + ", column " + std::to_string(parser_->cursor_position().col) + "! " + e.what());
    }
    catch(const std::logic_error& e)
    {
        throw std::logic_error("Logic Error at line " + std::to_string(parser_->cursor_position().row) + ", column " + std::to_string(parser_->cursor_position().col) + "! " + e.what());
    }
}