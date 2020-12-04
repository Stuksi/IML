#include "../include/Base Tag Classes/AttributeTag.h"

AttributeTag::AttributeTag() : attribute(nullptr)
{}

AttributeTag::~AttributeTag()
{
    delete attribute;
}

Attribute*& AttributeTag::getAttribute()
{
    return attribute;
}

Attribute* AttributeTag::getAttribute() const
{
    return attribute;
}

void AttributeTag::moveValuesToAttribute()
{
    throw;
}
