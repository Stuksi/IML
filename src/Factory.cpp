#include "../include/Factory.h"
#include "../include/Tags/Let.h"
#include "../include/Tags/MapInc.h"

Tag* Factory::sToTag(std::string type)
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