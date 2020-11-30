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
    TagType type;
    Tag *parent;
    Attribute attribute;
    std::vector<double> values;
public:
    Tag();
    virtual ~Tag();

    void setType(TagType);
    void setAttribute(Attribute);
    void setParent(Tag*);
    
    TagType getType() const;
    Attribute getAttribute() const;
    Tag* getParent() const;

    void addValue(double);
    void addValues(std::vector<double>);

    virtual std::vector<double> eval() const;
};

struct Factory
{
    static Tag* stot(std::string);
};

#endif