#ifndef __iml_token_h
#define __iml_token_h

#include <string>

enum class iml_token_type
{
    open_bracket,
    close_bracket,
    quote,
    slash,
    number,
    string,
    invalid
};

struct iml_token_position
{
    size_t row, col;    
};

struct iml_token
{
    iml_token_type type;
    std::string text;
    iml_token_position position;
};

#endif