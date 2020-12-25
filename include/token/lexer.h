#ifndef __lexer_h
#define __lexer_h

#include "lexer_result.h"
#include <iostream>

namespace iml
{
    class lexer
    {
    private:
        std::istream& in_;
        token next();
    public:
        lexer(std::istream&);
        lexer_result tokenize();
    };
}

#endif