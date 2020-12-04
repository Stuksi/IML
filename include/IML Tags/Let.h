#ifndef __Let_H
#define __Let_H

#include "../Base Tag Classes/AttributeTag.h"

class Let : public AttributeTag
{
public:
    Let();
    std::vector<double> eval() const;
    void setAttribute(Attribute);
    void moveValuesToAttribute();
};

#endif

