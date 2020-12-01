#include "../include/Tags/MapInc.h"

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

bool MapInc::hasStringAttribute() const
{
    return false;
}

bool MapInc::hasNumberAttribute() const
{
    return true;
}