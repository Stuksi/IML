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
private:
    TagType type;
    std::vector<double> values;
public:
    Tag() = default;
    virtual ~Tag() = default;

    void setType(TagType);
    void setValues(std::vector<double>);
    
    TagType getType() const;
    std::vector<double> getValues() const;

    void addValue(double);
    void addValue(std::vector<double>);

    virtual std::vector<double> eval() const = 0;
    virtual void setAttribute(Attribute);
    virtual Attribute*& getAttribute();
    virtual Attribute* getAttribute() const;
    virtual void moveValuesToAttribute();
};

#endif