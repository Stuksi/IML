#ifndef __iml_atag_h
#define __iml_atag_h

#include "iml_atag_base.h"

template <iml_tag_type T>
class iml_atag : public iml_atag_base
{
public:
    iml_atag(iml_attribute);

    iml_attribute configure(iml_attribute) const;
    std::list<double> evaluate() const;
    
};

#include "../src/template/iml_atag.cpp"

#endif