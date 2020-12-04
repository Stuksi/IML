#include "../include/Base Tag Classes/Tag.h"

void Tag::setType(TagType _type)
{
    type = _type;
}

void Tag::setValues(std::vector<double> _values)
{
    values = _values;
}

TagType Tag::getType() const
{
    return type;
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

void Tag::setAttribute(Attribute _attribute)
{
    throw;
}

Attribute*& Tag::getAttribute()
{
    throw;
}

Attribute* Tag::getAttribute() const
{
    throw;
}

void Tag::moveValuesToAttribute()
{
    throw;
}