#include "../include/Tag.h"

Tag::Tag() : attribute(Attribute()), type(Root)
{}

Tag::~Tag()
{}

void Tag::setType(TagType _type)
{
    type = _type;
}

void Tag::setAttribute(Attribute _attribute)
{
    attribute = _attribute;
}

void Tag::setValues(std::vector<double> _values)
{
    values = _values;
}

TagType Tag::getType() const
{
    return type;
}

Attribute& Tag::getAttribute()
{
    return attribute;
}

Attribute Tag::getAttribute() const
{
    return attribute;
}

std::vector<double> Tag::getValues() const
{
    return values;
}

void Tag::addValue(double value)
{
    values.push_back(value);
}

void Tag::addValue(std::vector<double> _values)
{
    for (double value : _values)
    {
        values.push_back(value);
    }
}

std::vector<double> Tag::eval() const
{
    return values;
}

bool Tag::hasAttribute() const
{
    return false;
}