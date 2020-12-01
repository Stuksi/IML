#ifndef __Tag_H
#define __Tag_H

#include "Attribute.h"

enum TagType
{
    Root,
    MAPINC,
    LET
};

class Tag
{
private:
    TagType type;
    Attribute attribute;
    Tag *parent;
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
    std::vector<double> getValues() const;

    void addValue(double);
    void addValue(std::vector<double>);

    virtual std::vector<double> eval() const;
    virtual bool hasStringAttribute() const;
    virtual bool hasNumberAttribute() const;
};

#endif