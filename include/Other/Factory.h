#ifndef __Factory_H
#define __Factory_H

#include "../Base Tag Classes/Tag.h"

class Factory
{
public:
    static Tag* stringToTag(std::string);
    static TagType stringToTagType(std::string);
};

#endif