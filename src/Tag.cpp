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

std::vector<double> Tag::eval() const
{
    return values;
}

Tag* Factory::stot(std::string type)
{
    return new Tag();
}