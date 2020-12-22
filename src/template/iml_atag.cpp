#ifndef __iml_atag_cpp
#define __iml_atag_cpp

#include "../../include/iml tag headers/iml_atag.h"

template <iml_tag_type T>
iml_atag<T>::iml_atag(iml_tag_attribute attribute) : iml_atag_base(T, configure(attribute))
{}

// ------------ MAP-INC
template <>
iml_tag_attribute iml_atag<iml_tag_type::map_inc>::configure(iml_tag_attribute attribute) const
{
    std::string text = attribute.text();
    if (!std::isdigit(text[0]) && text[0] != '-')
    {
        throw std::invalid_argument
            (
                "Tag MAP-INC supports attributes with real number values only, given "
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
    double attribute_number = stod(attribute().text());
    for (double& value : result_values)
    {
        value += attribute_number;
    }
    return result_values;
}

// ------------ MAP-MLT
template <>
iml_tag_attribute iml_atag<iml_tag_type::map_mlt>::configure(iml_tag_attribute attribute) const
{
    std::string text = attribute.text();
    if (!std::isdigit(text[0]) && text[0] != '-')
    {
        throw std::invalid_argument
            (
                "Tag MAP-MLT supports attributes with real number values only, given "
                + attribute.text() 
                + "!"
            );
    }
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::map_mlt>::evaluate() const
{
    std::list<double> result_values = values();
    double attribute_number = stod(attribute().text());
    for (double& value : result_values)
    {
        value *= attribute_number;
    }
    return result_values;
}

// ------------ SRT-ORD
template <>
iml_tag_attribute iml_atag<iml_tag_type::srt_ord>::configure(iml_tag_attribute attribute) const
{
    std::string text = attribute.text();
    if (text != "ASC" && text != "DSC")
    {
        throw std::invalid_argument
            (
                "Tag SRT-ORD supports attributes with string 'ASC' or 'DSC', given "
                + attribute.text() 
                + "!"
            );
    }
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::srt_ord>::evaluate() const
{
    std::list<double> result_values = values();
    std::string attribute_string = attribute().text();
    if (attribute_string == "ASC")
    {
        result_values.sort([](double a, double b)->bool{return a < b;});
    }
    else 
    {
        result_values.sort([](double a, double b)->bool{return a > b;});
    }
    return result_values;
}

// ------------ SRT-SLC
template <>
iml_tag_attribute iml_atag<iml_tag_type::srt_slc>::configure(iml_tag_attribute attribute) const
{
    std::string text = attribute.text();
    for (char c : text)
    {
        if (!isdigit(c))
        {
            throw std::invalid_argument
                (
                    "Tag SRT-SLC supports attributes with integer values only, given "
                    + attribute.text() 
                    + "!"
                );  
        }
    }    
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::srt_slc>::evaluate() const
{
    std::list<double> result_values;
    double attribute_number = stod(attribute().text());
    std::list<double>::iterator it = values().begin();
    std::advance(it, attribute_number);
    for (auto i = it; i != values().end(); ++i)
    {
        result_values.push_back(*i);
    }
    return result_values;
}

// ------------ LET
template <>
iml_tag_attribute iml_atag<iml_tag_type::let>::configure(iml_tag_attribute attribute) const
{
    std::string text = attribute.text();
    for (char c : text)
    {
        if (!(c >= 'A' && c <= 'Z'))
        {
            throw std::invalid_argument
                (
                    "Tag LET supports attributes with capital letter string values only, given "
                    + attribute.text() 
                    + "!"
                );  
        }
    }    
    return attribute;
}

template <>
std::list<double> iml_atag<iml_tag_type::let>::evaluate() const
{
    return values();
}


#endif