#ifndef __token_h
#define __token_h

#include "token_type.h"
#include <string>

namespace iml
{
    struct token
    {
        std::string text;
        token_type type;
    };  
}

#endif