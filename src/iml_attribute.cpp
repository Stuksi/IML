#include "../include/iml_attribute.h"

iml_attribute::iml_attribute(std::string _info) : info(_info)
{}

void iml_attribute::set(std::string _info)
{
    info = _info;
}

std::string iml_attribute::get() const
{
    return info;
}