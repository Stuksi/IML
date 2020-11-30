#include "../include/Attribute.h"

Attribute::Attribute() : id(""), type(Empty)
{}

void Attribute::setType(AttributeType _type)
{
    type = _type;
}

void Attribute::setId(std::string _id)
{
    id = _id;
}

void Attribute::setValues(std::vector<double> _values)
{
    values = _values;
}

AttributeType Attribute::getType() const
{
    return type;
}

std::string Attribute::getId() const
{
    return id;
}

std::vector<double> Attribute::getValues() const
{
    return values;
}
