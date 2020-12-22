#ifndef __iml_tokenizer_h
#define __iml_tokenizer_h

#include "iml_token.h"

#include <iostream>
#include <list>

class iml_tokenizer
{
private:
    std::istream& in_;
    iml_token_position position_;
    void cws();
    iml_token next();
    bool is_char();
    bool is_digit();
    iml_token read_string();
    iml_token read_number();    
    iml_token read_sign();
public:
    iml_tokenizer(std::istream&);
    std::list<iml_token> tokenize();
};

#endif