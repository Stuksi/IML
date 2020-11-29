#include "../include/Attribute.h"

#include <cstring>

Attribute::Attribute() : id(""), type(Empty)
{}

Attribute::Attribute(const char* _id) : type(AlphaNumeric)
{
    setId(_id);
}

void Attribute::setId(const char* _id)
{
    id = _id;
}

void Attribute::setType(AttributeType _type)
{
    type = _type;
}

std::string Attribute::getId() const
{
    return id;
}

AttributeType Attribute::getType() const
{
    return type;
}

ListAttribute::ListAttribute(const char* _id, const std::vector<double>& _values) : values(_values)
{
    setId(_id);
    setType(List);
}

ListAttribute::~ListAttribute()
{}

std::vector<double> ListAttribute::getValues() const
{
    return values;
}