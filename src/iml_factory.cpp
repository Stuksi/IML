#include "../include/iml_factory.h"
#include "../include/iml_tag.h"
#include "../include/iml_atag.h"

#include <stdexcept>

bool iml_factory::exists(std::string type)
{
    return type == "MAP-INC"
        || type == "LET";
}

iml_tag_base* iml_factory::to_tag(std::string type)
{
    iml_tag_type _type = to_type(type);
    iml_tag_base* tag;
    if (type == "")
    {

    }
    return tag;
}

iml_tag_base* iml_factory::to_atag(std::string type, iml_attribute attribute)
{
    iml_tag_base* tag;
    if (type == "MAP-INC")
    {
        tag = new iml_atag<iml_tag_type::map_inc>(attribute);
    }
    else if (type == "LET")
    {
        tag = new iml_atag<iml_tag_type::let>(attribute);
    }
    return tag;
}

iml_tag_type iml_factory::to_type(std::string type)
{
    if (type == "MAP-INC")
    {
        return iml_tag_type::map_inc;
    }
    else if (type == "LET")
    {
        return iml_tag_type::let;
    }
    return iml_tag_type::iml_root;
}

std::string iml_factory::to_string(iml_tag_type type)
{
    switch (type)
    {
    case iml_tag_type::map_inc: return "MAP-INC";
    case iml_tag_type::let: return "LET";    
    case iml_tag_type::iml_root: return "iml_root";    
    default: return "";
    }
}
