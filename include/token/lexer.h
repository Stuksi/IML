#ifndef __lexer_h
#define __lexer_h

#include "lexer_result.h"
#include <iostream>

namespace iml
{
    class lexer
    {
    private:
        std::istream& in;

        void cws();
        
        token next_sign();
        token next_string();
        token next_number();
        token next();
    public:
        lexer() = default;
        lexer(std::istream&);

        // Convert input to tokens
        lexer_result tokenize();
    };
}

#endif