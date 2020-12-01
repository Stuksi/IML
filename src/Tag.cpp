#include "../include/Tag.h"

Tag::Tag() : parent(nullptr), attribute(Attribute()), type(Root)
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

TagType Tag::getType() const
{
    return type;
}

Attribute Tag::getAttribute() const
{
    return attribute;
}

Tag* Tag::getParent() const
{
    return parent;
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

bool Tag::hasStringAttribute() const
{
    return false;
}

bool Tag::hasNumberAttribute() const
{
    return false;
}