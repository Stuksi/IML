#ifndef __Tag_H
#define __Tag_H

#include <vector>
#include "Attribute.h"

enum TagType
{
    Root
};

class Tag
{
private:
    std::vector<double> values;
    Attribute *attribute;
    Tag *parent;
    TagType type;
public:
    Tag();
    Tag(Tag*);
    Tag(Tag*, Attribute*);
    virtual ~Tag();

    void setType(TagType);

    Tag* getParent() const;
    Attribute* getAttribute() const;
    TagType getType() const;

    virtual std::vector<double> eval() const;
};

#endif