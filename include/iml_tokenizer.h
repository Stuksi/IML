#ifndef __IML_TOKENIZER_H
#define __IML_TOKENIZER_H

#include <iostream>
#include "../libs/list.h"

enum iml_token_type
{
    open_bracket,
    close_bracket,
    slash,
    quote,
    text,
    number,
    minus,
    error
};

struct iml_token
{
    iml_token_type type;
    char* s_val;
    double d_val;
};

struct iml_tokenizer_result
{
    list<iml_token> tokens;
};

class iml_tokenizer
{
private:
    std::istream& in;
    char cursor;

    bool is_text();
    bool is_digit();
    
    char* read_text();
    char* append_text(char*&);
    double read_number();

    void clear_white_spaces();
    
    void next();
    iml_token next_token();
public:
    iml_tokenizer(std::istream&);
    iml_tokenizer_result tokenize();
};

#endif