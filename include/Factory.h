#ifndef __Factory_H
#define __Factory_H

#include "Tag.h"

class Factory
{
public:
    static Tag* sToTag(std::string);
};

#endif