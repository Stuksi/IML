#ifndef __iml_atag_cpp
#define __iml_atag_cpp

#include "../../include/iml_atag.h"

#include <stdexcept>

template <iml_tag_type T>
iml_atag<T>::iml_atag(iml_attribute attribute) : iml_atag_base(T, configure(attribute))
{}


/// --------- map_inc 
template <>
iml_attribute iml_atag<iml_tag_type::map_inc>::configure(iml_attribute attribute) const
{
    if (attribute.text()[0] != '-' && !isdigit(attribute.text()[0]))
    {
        throw std::invalid_argument
        (
            "Attribute expects number, given "
            + attribute.text() 
            + "!"
        );
    }
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::map_inc>::evaluate() const
{
    std::list<double> result_values = values();
    long amplifier = std::stod(attribute().text());
    for (double& val : result_values)
    {
        val += amplifier;
    }
    return result_values;
}

/// --------- let 
template <>
iml_attribute iml_atag<iml_tag_type::let>::configure(iml_attribute attribute) const
{
    if (attribute.text()[0] == '-' || isdigit(attribute.text()[0]))
    {
        throw std::invalid_argument
        (
            "Attribute expects string, given " 
            + attribute.text() 
            + "!"
        );
    }
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::let>::evaluate() const
{
    return values();
}

#endif