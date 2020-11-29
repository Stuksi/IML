#include "../include/Factory.h"

Tag* Factory::sToTag(std::string type)
{
    return new Tag();
}