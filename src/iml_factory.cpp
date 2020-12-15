#include "../include/iml_factory.h"
#include "../include/iml_tag_list.h"

#include <stdexcept>

iml_tag* iml_factory::stotag(std::string type)
{
    if (type == "MAP-INC")
    {
        return new iml_map_inc();
    }
    else if (type == "LET")
    {
        return new iml_let();
    }
    throw std::invalid_argument("Tag " + type + " does not exist!");
}

iml_tag_type iml_factory::stotype(std::string type)
{
    if (type == "MAP-INC")
    {
        return iml_tag_type::map_inc;
    }
    else if (type == "LET")
    {
        return iml_tag_type::let;
    }
    throw std::invalid_argument("Tag " + type + " does not exist!");
}

std::string iml_factory::typetos(iml_tag_type type)
{
    switch (type)
    {
    case iml_tag_type::map_inc: return "MAP-INC";
    case iml_tag_type::let: return "LET";    
    default: return "";
    }
}
