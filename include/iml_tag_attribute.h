#ifndef __iml_tag_attribute_h
#define __iml_tag_attribute_h

#include "iml_tag_attribute_base.h"

template <iml_tag_type T>
class iml_tag_attribute : public iml_tag_attribute_base
{
public:
    iml_tag_attribute() = default;
    iml_tag_attribute(iml_attribute);
    ~iml_tag_attribute() = default;

    iml_attribute assert(iml_attribute) const;
    std::list<double> eval() const;
};

#include "../src/template/iml_tag_attribute.cpp"

#endif