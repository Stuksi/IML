#include "../include/Factory.h"
#include "../include/TagList.h"

Tag* Factory::stringToTag(std::string type)
{
    if (type == "MAP-INC")
    {
        return new MapInc();
    }
    else if (type == "LET")
    {
        return new Let();
    }
    throw;
}

TagType Factory::stringToTagType(std::string type)
{
    if (type == "MAP-INC")
    {
        return MAPINC;
    }
    else if (type == "LET")
    {
        return LET;
    }
    throw;
}