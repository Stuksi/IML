#include "../include/iml tag headers/iml_tag_attribute.h"

iml_tag_attribute::iml_tag_attribute(std::string text) : text_(text)
{}

std::string iml_tag_attribute::text() const
{
    return text_;
}

bool iml_tag_attribute::empty() const
{
    return text_ == "";
}