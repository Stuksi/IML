#include "../include/iml_tag.h"

void iml_tag::add_value(char* val)
{
    lst.append(val);
}

iml_attribute* iml_tag::attribute() const
{
    return _attribute;
}

iml_tag_type iml_tag::type() const
{
    return _type;
}