#include "../include/iml_tag_attribute_base.h"

iml_tag_attribute_base::iml_tag_attribute_base(iml_tag_type type, iml_attribute attribute) : iml_tag_base(type), attribute_(attribute)
{}

iml_attribute iml_tag_attribute_base::attribute() const
{
    return attribute_;
}