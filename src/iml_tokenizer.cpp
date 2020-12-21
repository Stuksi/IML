#include "../include/iml_tokenizer.h"

#include <stdexcept>

iml_tokenizer::iml_tokenizer(std::istream& in) : in_(in), position_(iml_token_position {1, 1})
{}

bool iml_tokenizer::is_char()
{
    return in_.peek() >= 'A' && in_.peek() <= 'Z';
}

bool iml_tokenizer::is_digit()
{
    return in_.peek() >= '0' && in_.peek() <= '9';
}

iml_token iml_tokenizer::read_string()
{
    std::string text = "";

    /// The strings can contain letters (upper-case) and dashes.
    while (is_char() || in_.peek() == '-')
    {
        text += in_.get();
    }

    iml_token_position token_position = position_;
    position_.col += text.length();

    return iml_token {iml_token_type::string, text, token_position};
}

iml_token iml_tokenizer::read_number()
{
    std::string number = "";
    
    /// Check for negative numbers.
    if (in_.peek() == '-')
    {
        number = "-";
        in_.get();
    }

    /// The number must contain at least one digit.
    if (!is_digit())
    {
        throw std::runtime_error
        (
            "Syntax Error at line " 
            + std::to_string(position_.row) 
            + ", column " 
            + std::to_string(position_.col) 
            + "! Expected number, given " 
            + std::string(1, in_.peek()) 
            + " !"
        );
    }

    /// Check if the number starts with a zero.
    if (in_.peek() == '0')
    {
        in_.get();

        /// If the number starts with a zero, a digit must not follow. 
        if (is_digit())
        {
            throw std::runtime_error
            (
                "Syntax Error at line " 
                + std::to_string(position_.row) 
                + ", column " 
                + std::to_string(position_.col) 
                + "! A number cannot have a leading zero and following digits!"
            );
        } 
        number += "0";
    }
    else
    {
        while (is_digit())
        {
            number += in_.get();
        }
    }

    /// Check for a floating point number.
    if (in_.peek() == '.')
    {
        number += in_.get();
        
        /// It is a syntax error if a digit doesn't follow after the floating point.
        if (!is_digit())
        {
            throw std::runtime_error(
                "Syntax Error at line " 
                + std::to_string(position_.row) 
                + ", column " 
                + std::to_string(position_.col) 
                + "! A number must have digits after dot '.' sign!");
        }
            
        while (is_digit())
        {
            number += in_.get();
        }
    }
        
    iml_token_position token_position = position_;
    position_.col += number.length();

    return iml_token {iml_token_type::number, number, token_position};
}

iml_token iml_tokenizer::read_sign()
{
    char current = in_.get();

    iml_token_position token_position = position_;
    position_.col += 1;
    
    switch (current)
    {
        case '<': return iml_token {iml_token_type::open_bracket, "<", token_position};
        case '>': return iml_token {iml_token_type::close_bracket, ">", token_position};
        case '"': return iml_token {iml_token_type::quote, "\"", token_position};
        case '/': return iml_token {iml_token_type::slash, "/", token_position};
        default : return iml_token {iml_token_type::invalid, std::string(1, current), token_position};
    }
}

void iml_tokenizer::cws()
{
    while (in_.peek() == ' ' || in_.peek() == '\n')
    {
        if (in_.peek() == ' ')
        {
            position_.col++;
        }
        else
        {
            position_.row++;
            position_.col = 1;
        }
        
        in_.get();
    }
}

iml_token iml_tokenizer::next()
{
    cws();
 
    if (in_.peek() == '-' || is_digit())
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

    while (true)
    {
        current = next();

        /// Check for the end of file character in the stream. The character has a value of -1.
        if (in_.eof() && current.text == std::string(1, -1))
        {
            break;
        }

        if (current.type == iml_token_type::invalid)
        {
            throw std::runtime_error
            (
                "Syntax Error at line " 
                + std::to_string(current.position.row) 
                + ", column " 
                + std::to_string(current.position.col) 
                + "! Unrecognized character " 
                + current.text 
                + "!"
            );
        }

        t_list.push_back(current);
    }

    /// A token indicating the end of the file position.
    t_list.push_back(iml_token {iml_token_type::invalid, "end_of_file()", position_});
    
    return t_list;
}