#include "../include/iml_root_tag.h"

iml_root_tag::iml_root_tag()
{
    tag_type = iml_tag_type::iml_root;
}

std::list<double> iml_root_tag::eval()
{
    return values;
}