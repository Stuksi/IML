#ifndef __iml_tag_attribute_base_h
#define __iml_tag_attribute_base_h

#include "iml_tag_base.h"

class iml_tag_attribute_base : public iml_tag_base
{
private:
    iml_attribute attribute_;

public:
    iml_tag_attribute_base() = default;
    iml_tag_attribute_base(iml_tag_type, iml_attribute);
    virtual ~iml_tag_attribute_base() = default;

    iml_attribute attribute() const;

    virtual iml_attribute assert(iml_attribute) const = 0;
    virtual std::list<double> eval() const = 0;
    
};

#endif