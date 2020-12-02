#include "../include/TagList.h"

// --------------------------------------- LET ---------------------------------------  // 

Let::Let()
{
    setType(LET);
}

std::vector<double> Let::eval() const
{
    return getValues();
}

bool Let::hasAttribute() const
{
    return true;
}

// --------------------------------------- MAP-INC ---------------------------------------  // 

MapInc::MapInc()
{
    setType(MAPINC);
}

std::vector<double> MapInc::eval() const
{
    std::vector<double> copy_values = getValues();
    double attributeValue = stod(getAttribute().getId()); 
    for (size_t i = 0; i < copy_values.size(); i++)
    {
        copy_values[i] += attributeValue;
    }
    return copy_values;
}

bool MapInc::hasAttribute() const
{
    return true;
}