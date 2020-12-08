#ifndef __Let_H
#define __Let_H

#include "../Base Tag Classes/AttributeTag.h"

class Let : public AttributeTag
{
public:
    Let();
    DLList<double> eval() const;
    void setAttribute(Attribute);
};

#endif

