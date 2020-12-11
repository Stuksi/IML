#include "../include/iml_tag_attribute.h"

#include <stdexcept>

iml_attribute iml_tag_attribute::get_attribute() const
{
    return attribute;
}

void iml_tag_attribute::set_attribute(iml_attribute _attribute)
{
    if (!attribute_type && (std::isdigit(_attribute.get()[0]) || _attribute.get()[0] == '-'))
    {
        throw std::invalid_argument("Attribute expects string, given " + _attribute.get() + "!");
    }
    else if (attribute_type && (!std::isdigit(_attribute.get()[0]) && _attribute.get()[0] != '-'))
    {
        throw std::invalid_argument("Attribute expects number, given " + _attribute.get() + "!");
    }
    attribute = _attribute;
}