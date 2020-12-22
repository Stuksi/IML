#include "../include/iml tag headers/iml_atag_base.h"

iml_atag_base::iml_atag_base(iml_tag_type type, iml_tag_attribute attribute) : iml_tag_base(type), attribute_(attribute) 
{}

iml_tag_attribute iml_atag_base::attribute() const
{
    return attribute_;
}