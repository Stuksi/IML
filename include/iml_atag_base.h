#ifndef __iml_atag_base_h
#define __iml_atag_base_h

#include "iml_tag_base.h"

class iml_atag_base : public iml_tag_base
{
private:
    iml_attribute attribute_;

public:
    iml_atag_base(iml_tag_type, iml_attribute);

    iml_attribute attribute() const;

    virtual iml_attribute configure(iml_attribute) const = 0;
    virtual std::list<double> evaluate() const = 0;
    
};

#endif