#include "../include/Tags/Let.h"

Let::Let()
{
    setType(LET);
}

std::vector<double> Let::eval() const
{
    return getValues();
}

bool Let::hasStringAttribute() const
{
    return true;
}

bool Let::hasNumberAttribute() const
{
    return false;
}