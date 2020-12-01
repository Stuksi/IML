#ifndef __Let_H
#define __Let_H

#include "../Tag.h"

class Let : public Tag
{
public:
    Let();
    std::vector<double> eval() const;
    bool hasStringAttribute() const;
    bool hasNumberAttribute() const;
};

#endif