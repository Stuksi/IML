#ifndef __Tag_H
#define __Tag_H

#include "Attribute.h"

enum TagType
{
    Root
};

class Tag
{
private:
    std::vector<double> values;
    Attribute attribute;
    Tag *parent;
    TagType type;
public:
    Tag();
    virtual ~Tag();

    void setType(TagType);
    void setAttribute(Attribute);
    void setParent(Tag*);
    
    Tag* getParent() const;
    Attribute getAttribute() const;
    TagType getType() const;

    void addValue(double);
    void addValues(std::vector<double>);

    virtual std::vector<double> eval() const;
};

#endif