#include "../include/iml_tag_attribute.h"

#include <stdexcept>

iml_attribute iml_tag_attribute::get_attribute() const
{
    return attribute;
}