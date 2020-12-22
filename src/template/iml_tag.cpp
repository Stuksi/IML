#ifndef __iml_tag_cpp
#define __iml_tag_cpp

#include "../../include/iml tag headers/iml_tag.h"
#include <unordered_set>

template <iml_tag_type T>
iml_tag<T>::iml_tag() : iml_tag_base(T)
{}

// ------------ ROOT
template <>
std::list<double> iml_tag<iml_tag_type::root>::evaluate() const
{
    return values();
}

// ------------ AGG-SUM
template <>
std::list<double> iml_tag<iml_tag_type::agg_sum>::evaluate() const
{
    if (values().empty())
    {
        return std::list<double>();
    }
    double result_value = 0;
    for (double value : values())
    {
        result_value += value;
    } 
    return {result_value};
}

// ------------ AGG-PRO
template <>
std::list<double> iml_tag<iml_tag_type::agg_pro>::evaluate() const
{
    if (values().empty())
    {
        return std::list<double>();
    }
    double result_value = 1;
    for (double value : values())
    {
        result_value *= value;
    } 
    return {result_value};
}

// ------------ AGG-AVG
template <>
std::list<double> iml_tag<iml_tag_type::agg_avg>::evaluate() const
{
    if (values().empty())
    {
        return std::list<double>();
    }
    double result_value = 0;
    for (double value : values())
    {
        result_value += value;
    } 
    return {result_value/values().size()};
}

// ------------ AGG-FST
template <>
std::list<double> iml_tag<iml_tag_type::agg_fst>::evaluate() const
{
    if (values().empty())
    {
        return std::list<double>();
    }
    return {*(values().begin())};
}

// ------------ AGG-LST
template <>
std::list<double> iml_tag<iml_tag_type::agg_lst>::evaluate() const
{
    if (values().empty())
    {
        return std::list<double>();
    }
    return {*(--(values().end()))};
}

// ------------ SRT-REV
template <>
std::list<double> iml_tag<iml_tag_type::srt_rev>::evaluate() const
{
    std::list<double> result_values;
    for (auto i = values().begin(); i != values().end(); ++i)
    {
        result_values.push_front(*i);
    }
    return result_values;
}

// ------------ SRT-DST
template <>
std::list<double> iml_tag<iml_tag_type::srt_dst>::evaluate() const
{
    std::unordered_set<double> values_set;
    std::list<double> result_values;
    for (auto i = values().begin(); i != values().end(); ++i)
    {
        if (values_set.find(*i) == values_set.end())
        {
            result_values.push_back(*i);
        }
    }
    return result_values;
}

// ------------ BODY
template <>
std::list<double> iml_tag<iml_tag_type::body>::evaluate() const
{
    return values();
}

#endif