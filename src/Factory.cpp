#include "../include/Other/Factory.h"
#include "../include/IML Tags/MapInc.h"
#include "../include/IML Tags/Let.h"

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
        return TagType::MAPINC;
    }
    else if (type == "LET")
    {
        return TagType::LET;
    }
    throw;
}