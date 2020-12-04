#ifndef __TagList_H
#define __TagList_H

#include "Tag.h"

struct Let : public AttributeTag
{
    Let();
    std::vector<double> eval() const;
    void setAttribute(Attribute);
};

struct MapInc : public AttributeTag
{
    MapInc();
    std::vector<double> eval() const;
    void setAttribute(Attribute);
};

#endif