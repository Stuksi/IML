#include "../include/iml tag headers/iml_tag_base.h"
#include "../include/iml tag headers/iml_tag_type_converter.h"
#include <stdexcept>

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

void iml_tag_base::clear()
{
    values_.clear();
}

iml_tag_attribute iml_tag_base::attribute() const
{
    throw std::logic_error("Tag " + iml_tag_type_converter::types[(int)type_] + " does not support attributes!");
}