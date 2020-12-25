#ifndef __lexer_result_h
#define __lexer_result_h

#include "token.h"
#include <list>

namespace iml
{
    struct lexer_result
    {
        std::list<token> tokens; 
    };
}

#endif