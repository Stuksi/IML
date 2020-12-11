#include "../include/iml_tag_attribute_list.h"

// -------------------------------------- // iml_map_inc // -------------------------------------- //

iml_map_inc::iml_map_inc()
{
    tag_type = iml_tag_type::map_inc;
    attribute_type = 1;
}

std::list<double> iml_map_inc::eval()
{
    double attribute_value = stod(attribute.get()); 
    for (auto i = values.begin(); i != values.end(); ++i)
    {
        *i += attribute_value;
    }
    return values;
}

// -------------------------------------- // iml_let // // -------------------------------------- //

iml_let::iml_let()
{
    tag_type = iml_tag_type::let;
    attribute_type = 0;
}

std::list<double> iml_let::eval()
{
    return values;
}