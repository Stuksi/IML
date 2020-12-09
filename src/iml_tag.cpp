#include "../include/iml_tag.h"

iml_tag_type iml_tag::type() const
{
    return tag_type;
}

void iml_tag::set_values(dllist<double> _values)
{
    values = _values;
}

dllist<double> iml_tag::get_values() const
{
    return values;
}

void iml_tag::add_value(double value)
{
    values.append(value);
}

void iml_tag::add_values(dllist<double> _values)
{
    for (double value : _values)
    {
        values.append(value);
    }
}

void iml_tag::set_attribute(iml_attribute _attribute)
{
    throw;
}

iml_attribute iml_tag::get_attribute() const
{
    throw;
}