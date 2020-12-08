#ifndef __Tag_H
#define __Tag_H

#include "../Attribute Classes/Attribute.h"

enum class TagType
{
    ROOT,
    MAPINC,
    LET
};

class Tag
{
protected:
    TagType type;
    DLList<double> values;
public: 
    Tag() = default;
    virtual ~Tag() = default;

    void setType(TagType);
    void setValues(DLList<double>);
    
    TagType getType() const;
    DLList<double> getValues() const;

    void addValue(double);
    void addValue(DLList<double>);

    virtual DLList<double> eval() const = 0;
    virtual void setAttribute(Attribute);
    virtual Attribute getAttribute() const;
};

#endif