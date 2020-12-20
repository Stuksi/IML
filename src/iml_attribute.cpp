#include "../include/iml_attribute.h"

iml_attribute::iml_attribute(std::string text) : text_(text)
{}

std::string iml_attribute::text() const
{
    return text_;
}

bool iml_attribute::empty() const
{
    return text_ == "";
}