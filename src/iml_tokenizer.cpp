#include "../include/iml_tokenizer.h"

#include <stdexcept>

iml_tokenizer::iml_tokenizer(std::istream& _in) : in(_in), position(iml_token_position {1, 1})
{}

bool iml_tokenizer::is_char()
{
    return in.peek() >= 'A' && in.peek() <= 'Z';
}

bool iml_tokenizer::is_digit()
{
    return in.peek() >= '0' && in.peek() <= '9';
}

iml_token iml_tokenizer::read_string()
{
    std::string text = "";
    while (is_char() || in.peek() == '-')
    {
        text += in.get();
    }
    iml_token_position token_position = position;
    position.col += text.length();
    return iml_token {iml_token_type::string, text, token_position};
}

iml_token iml_tokenizer::read_number()
{
    std::string number = "";
    if (in.peek() == '-')
    {
        number = "-";
        in.get();
    }
    if (in.peek() == '0')
    {
        in.get();
        if (is_digit())
        {
            throw std::runtime_error("Syntax Error at line " + std::to_string(position.row) + ", column " + std::to_string(position.col) + "! A number cannot have a leading zero and following digits!");
        }
        number += "0";
    } else {
        while (is_digit())
        {
            number += in.get();
        }
    }
    if (in.peek() == '.')
    {
        number += in.get();
        if (!is_digit())
        { 
            throw std::runtime_error("Syntax Error at line " + std::to_string(position.row) + ", column " + std::to_string(position.col) + "! A number must have digits after dot '.' sign!");
        }
        while (is_digit())
        {
            number += in.get();
        }
    }
    iml_token_position token_position = position;
    position.col += number.length();
    return iml_token {iml_token_type::number, number, token_position};
}

iml_token iml_tokenizer::read_sign()
{
    char current = in.get();
    iml_token_position token_position = position;
    position.col += 1;
    switch (current)
    {
        case '<': return iml_token {iml_token_type::open_bracket, "<", token_position};
        case '>': return iml_token {iml_token_type::close_bracket, ">", token_position};
        case '"': return iml_token {iml_token_type::quote, "\"", token_position};
        case '/': return iml_token {iml_token_type::slash, "/", token_position};
        default : return iml_token {iml_token_type::invalid, "" + current, token_position};
    }
}

void iml_tokenizer::clear_white_spaces()
{
    while (in.peek() == ' ' || in.peek() == '\n')
    {
        if (in.peek() == ' ')
        {
            position.col++;
        }
        else
        {
            position.row++;
            position.col = 1;
        }
        in.get();
    }
}

iml_token iml_tokenizer::next_token()
{
    clear_white_spaces();
    if (in.peek() == '-' || is_digit())
    {
        return read_number();
    }
    else if (is_char())
    {
        return read_string();
    }
    return read_sign();
}

std::list<iml_token> iml_tokenizer::tokenize()
{
    std::list<iml_token> t_list;
    iml_token current;
    while (!in.eof())
    {
        current = next_token();
        if (current.type == iml_token_type::invalid)
        {
            throw std::runtime_error("Syntax Error at line " + std::to_string(position.row) + ", column " + std::to_string(position.col) + "! Unrecognized character " + current.text + "!");
        }
        t_list.push_back(current);
    }
    t_list.push_back(iml_token {iml_token_type::invalid, "end_of_file()", position});
    return t_list;
}