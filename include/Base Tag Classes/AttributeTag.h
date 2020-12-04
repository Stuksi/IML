#ifndef __AttributeTag_H
#define __AttributeTag_H

#include "Tag.h"

class AttributeTag : public Tag
{
private:
    Attribute *attribute;
public:
    AttributeTag();
    AttributeTag(const AttributeTag&) = delete;
    AttributeTag& operator= (const AttributeTag&) = delete;
    virtual ~AttributeTag();
    
    Attribute*& getAttribute();
    Attribute* getAttribute() const;

    virtual std::vector<double> eval() const = 0;
    virtual void moveValuesToAttribute();
};

#endif