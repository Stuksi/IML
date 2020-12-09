#include "../include/iml_factory.h"
#include "../include/iml_tag_attribute_list.h"

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
    throw;
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
    throw;
}