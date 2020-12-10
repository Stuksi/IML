#include "../include/iml_tag.h"
#include "../include/iml_factory.h"

#include <stdexcept>

iml_tag_type iml_tag::type() const
{
    return tag_type;
}

void iml_tag::set_values(std::list<double> _values)
{
    values = _values;
}

void iml_tag::add_value(double value)
{
    values.push_back(value);
}

void iml_tag::add_values(std::list<double> _values)
{
    for (double value : _values)
    {
        values.push_back(value);
    }
}

void iml_tag::set_attribute(iml_attribute _attribute)
{
    throw std::logic_error("Tag " + iml_factory::typetos(tag_type) + " does not support attributes!");
}

iml_attribute iml_tag::get_attribute() const
{
    throw std::logic_error("Tag " + iml_factory::typetos(tag_type) + " does not support attributes!");
}