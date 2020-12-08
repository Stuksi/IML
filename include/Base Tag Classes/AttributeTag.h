#ifndef __AttributeTag_H
#define __AttributeTag_H

#include "Tag.h"

class AttributeTag : public Tag
{
protected:
    Attribute attribute;
public:
    AttributeTag() = default;
    virtual ~AttributeTag() = default;

    Attribute getAttribute() const;
    virtual DLList<double> eval() const = 0;
};

#endif