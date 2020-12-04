#include "../include/IML Tags/MapInc.h"

MapInc::MapInc()
{
    setType(TagType::MAPINC);
}

std::vector<double> MapInc::eval() const
{
    std::vector<double> copy_values = getValues();
    double attributeValue = stod(getAttribute()->getId()); 
    for (size_t i = 0; i < copy_values.size(); i++)
    {
        copy_values[i] += attributeValue;
    }
    return copy_values;
}

void MapInc::setAttribute(Attribute _attribute)
{
    if (!std::isdigit(_attribute.getId()[0]) && _attribute.getId()[0] != '-') throw;
    getAttribute() = new Attribute(_attribute.getId());
}