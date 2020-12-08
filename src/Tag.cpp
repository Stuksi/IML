#include "../include/Base Tag Classes/Tag.h"

void Tag::setType(TagType _type)
{
    type = _type;
}

void Tag::setValues(DLList<double> _values)
{
    values = _values;
}

TagType Tag::getType() const
{
    return type;
}

DLList<double> Tag::getValues() const
{
    return values;
}

void Tag::addValue(double value)
{
    values.append(value);
}

void Tag::addValue(DLList<double> _values)
{
    for (double value : _values)
    {
        values.append(value);
    }
}

void Tag::setAttribute(Attribute _attribute)
{
    throw;
}

Attribute Tag::getAttribute() const
{
    throw;
}