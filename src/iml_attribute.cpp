#include "../include/iml_attribute.h"

iml_attribute::iml_attribute(std::string attribute_info) : info(attribute_info)
{}

void iml_attribute::set(std::string attribute_info)
{
    info = attribute_info;
}

std::string iml_attribute::get() const
{
    return info;
}