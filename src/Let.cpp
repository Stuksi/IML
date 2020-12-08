#include "../include/IML Tags/Let.h"

Let::Let()
{
    type = TagType::LET;
}

DLList<double> Let::eval() const
{
    return values;
}

void Let::setAttribute(Attribute _attribute)
{
    if(std::isdigit(_attribute.getId()[0])) throw;
    attribute = _attribute;
}