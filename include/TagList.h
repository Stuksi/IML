#ifndef __TagList_H
#define __TagList_H

#include "Tag.h"

struct Let : public Tag
{
    Let();
    std::vector<double> eval() const;
    bool hasAttribute() const;
};

struct MapInc : public Tag
{
    MapInc();
    std::vector<double> eval() const;
    bool hasAttribute() const;
};

#endif