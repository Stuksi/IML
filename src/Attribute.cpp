#include "../include/Attribute.h"

Attribute::Attribute() : id("")
{}

Attribute::Attribute(std::string _id) : id(_id)
{}


void Attribute::setId(std::string _id)
{
    id = _id;
}

void Attribute::setValues(std::vector<double> _values)
{
    values = _values;
}

std::string Attribute::getId() const
{
    return id;
}

std::vector<double> Attribute::getValues() const
{
    return values;
}

