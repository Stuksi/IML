#ifndef __iml_token_h
#define __iml_token_h

#include "iml_token_type.h"
#include "iml_token_position.h"
#include <string>

class iml_token
{
public:
    iml_token_type type;
    std::string text;
    iml_token_position position;
};

#endif