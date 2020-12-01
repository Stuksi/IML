#ifndef __MapInc_H
#define __MapInc_H

#include "../Tag.h"

class MapInc : public Tag
{
public:
    MapInc();
    std::vector<double> eval() const;
    bool hasStringAttribute() const;
    bool hasNumberAttribute() const;
};

#endif