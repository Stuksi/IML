#ifndef __iml_tokenizer_h
#define __iml_tokenizer_h

#include <iostream>
#include <string>
#include "../ds/dllist.h"

enum class iml_token_type
{
    open_bracket, // '<'
    close_bracket, // '>'
    quote, // '"'
    slash, // '/'
    number, // (-inf ... inf)   
    string, // ('A' ... 'Z')
    invalid // '?'
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

class iml_tokenizer
{
private:
    std::istream& in;
    iml_token_position position;

    void clear_white_spaces();
    iml_token next_token();

    bool is_char();
    bool is_digit();

    iml_token read_string();
    iml_token read_number();
    iml_token read_sign();
public:
    iml_tokenizer(std::istream&);
    dllist<iml_token> tokenize();
};

#endif