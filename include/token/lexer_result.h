#ifndef __lexer_result_h
#define __lexer_result_h

#include "token.h"
#include <list>

namespace iml
{
    class lexer_result
    {
    public:
        lexer_result() = default;
        lexer_result(std::list<token>);
        std::list<token> tokens;
        std::list<token>::iterator tokens_it;
    };
}

#endif