#include "../include/Tag.h"

Tag::Tag() : parent(0), attribute(0), type(Root)
{}

Tag::Tag(Tag* _parent) : parent(_parent), attribute(new Attribute())
{}

Tag::Tag(Tag* _parent, Attribute* _attribute) : parent(_parent), attribute(_attribute)
{}

Tag::~Tag()
{
    delete attribute;
}

void Tag::setType(TagType _type)
{
    type = _type;
}

Tag* Tag::getParent() const
{
    return parent;
}

Attribute* Tag::getAttribute() const
{
    return attribute;
}

TagType Tag::getType() const
{
    return type;
}

std::vector<double> Tag::eval() const
{
    return values;
}