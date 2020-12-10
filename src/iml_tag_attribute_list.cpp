#include "../include/iml_tag_attribute_list.h"

#include <stdexcept>

// -------------------------------------- // iml_map_inc // -------------------------------------- //

iml_map_inc::iml_map_inc()
{
    tag_type = iml_tag_type::map_inc;
}

void iml_map_inc::set_attribute(iml_attribute _attribute)
{
    if (!std::isdigit(_attribute.get()[0]) && _attribute.get()[0] != '-')
    {
        throw std::invalid_argument("Attribute expects number, given " + _attribute.get() + "!");
    }
    attribute = _attribute;
}

std::list<double> iml_map_inc::eval()
{
    double attribute_value = stod(attribute.get()); 
    for (auto i = values.begin(); i != values.end(); ++i)
    {
        *i += attribute_value;
    }
    return values;
}

// -------------------------------------- // iml_let // // -------------------------------------- //

iml_let::iml_let()
{
    tag_type = iml_tag_type::let;
}

void iml_let::set_attribute(iml_attribute _attribute)
{
    if (std::isdigit(_attribute.get()[0]) || _attribute.get()[0] == '-')
    {
        throw std::invalid_argument("Attribute expects string, given " + _attribute.get() + "!");
    }
    attribute = _attribute;
}

std::list<double> iml_let::eval()
{
    return values;
}