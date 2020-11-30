#include "../include/Tag.h"

Tag::Tag() : parent(0), attribute(Attribute()), type(Root)
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

void Tag::setParent(Tag* _parent)
{
    parent = _parent;
}

Tag* Tag::getParent() const
{
    return parent;
}

Attribute Tag::getAttribute() const
{
    return attribute;
}

TagType Tag::getType() const
{
    return type;
}

std::vector<double> Tag::eval() const
{
    return values;
}

void Tag::addValue(double value)
{
    values.push_back(value);
}

void Tag::addValues(std::vector<double> _values)
{
    for (double value : _values)
    {
        values.push_back(value);
    }
}

