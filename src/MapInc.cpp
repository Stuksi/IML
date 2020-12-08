#include "../include/IML Tags/MapInc.h"

MapInc::MapInc()
{
    type = TagType::MAPINC;
}

DLList<double> MapInc::eval() const
{
    double attributeValue = stod(attribute.getId()); 
    // REWORK????
    DLList<double> _values = values;
    for (auto i = _values.begin(); i != _values.end(); ++i)
    {
        *i += attributeValue;
    }
    return _values;
}

void MapInc::setAttribute(Attribute _attribute)
{
    if (!std::isdigit(_attribute.getId()[0]) && _attribute.getId()[0] != '-') throw;
    attribute = _attribute;
}