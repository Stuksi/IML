#ifndef __iml_tag_attribute_h
#define __iml_tag_attribute_h

#include "iml_tag.h"

class iml_tag_attribute : public iml_tag
{
protected:
    iml_attribute attribute;
    int attribute_type; // 0 -> string ; 1 -> numeric
public:
    iml_attribute get_attribute() const;
    void set_attribute(iml_attribute);

    virtual std::list<double> eval() = 0;
};

#endif