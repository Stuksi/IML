#ifndef __MapInc_H
#define __MapInc_H

#include "../Base Tag Classes/AttributeTag.h"

class MapInc : public AttributeTag
{
public:
    MapInc();
    DLList<double> eval() const;
    void setAttribute(Attribute);
};

#endif