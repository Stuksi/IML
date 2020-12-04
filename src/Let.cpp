#include "../include/IML Tags/Let.h"
#include "../include/Attribute Classes/AttributeList.h"

Let::Let()
{
    setType(TagType::LET);
}

std::vector<double> Let::eval() const
{
    return getValues();
}

void Let::setAttribute(Attribute _attribute)
{
    if(std::isdigit(_attribute.getId()[0])) throw;
    getAttribute() = new AttributeList(_attribute.getId());
}

void Let::moveValuesToAttribute()
{
    getAttribute()->setValues(eval());
    setValues(std::vector<double>());
}