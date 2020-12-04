#include "../include/Attribute Classes/Attribute.h"

Attribute::Attribute(std::string _id) : id(_id)
{}

void Attribute::setId(std::string _id)
{
    id = _id;
}

std::string Attribute::getId() const
{
    return id;
}

void Attribute::setValues(std::vector<double> _values)
{
    throw;
}

std::vector<double> Attribute::getValues() const
{
    throw;
}

