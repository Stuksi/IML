#ifndef __iml_tag_attribute_cpp
#define __iml_tag_attribute_cpp

#include "../../include/iml_tag_attribute.h"

template <iml_tag_type T>
iml_tag_attribute<T>::iml_tag_attribute(iml_attribute attribute) : iml_tag_attribute_base(T, assert(attribute))
{}

// ======================= // MAP-INC // ======================= //

template <>
iml_attribute iml_tag_attribute<iml_tag_type::map_inc>::assert(iml_attribute attribute) const
{
    if (attribute.text()[0] != '-' && !isdigit(attribute.text()[0]))
    {
        throw;
    }
    return attribute;
}

template <>
std::list<double> iml_tag_attribute<iml_tag_type::map_inc>::eval() const
{
    std::list<double> result_values = values();
    long amplifier = std::stod(attribute().text());
    for (double& val : result_values)
    {
        val += amplifier;
    }
    return result_values;
}

// ======================= // LET // ======================= //

template <>
iml_attribute iml_tag_attribute<iml_tag_type::let>::assert(iml_attribute attribute) const
{
    if (attribute.text()[0] == '-' || isdigit(attribute.text()[0]))
    {
        throw;
    }
    return attribute;
}

template <>
std::list<double> iml_tag_attribute<iml_tag_type::let>::eval() const
{
    return values();
}

#endif