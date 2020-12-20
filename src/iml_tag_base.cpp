#include "../include/iml_tag_base.h"

iml_tag_base::iml_tag_base(iml_tag_type type) : type_(type)
{}

iml_tag_type iml_tag_base::type() const
{
    return type_;
}

std::list<double> iml_tag_base::values() const
{
    return values_;
}

void iml_tag_base::add(std::list<double> values)
{
    for (double value : values)
    {
        values_.push_back(value);
    }
}

void iml_tag_base::add(double value)
{
    values_.push_back(value);
}

void iml_tag_base::clear()
{
    values_ = {};
}

iml_attribute iml_tag_base::attribute() const
{
    throw;
}