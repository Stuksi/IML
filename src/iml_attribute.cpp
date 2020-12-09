#include "../include/iml_attribute.h"

void iml_attribute::set(std::string _info)
{
    info = _info;
}

std::string iml_attribute::get() const
{
    return info;
}