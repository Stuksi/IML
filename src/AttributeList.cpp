#include "../include/Attribute Classes/AttributeList.h"

AttributeList::AttributeList(std::string id)
{
    setId(id);
}

void AttributeList::setValues(std::vector<double> _values)
{
    values = _values;
}

std::vector<double> AttributeList::getValues() const
{
    return values;
}
