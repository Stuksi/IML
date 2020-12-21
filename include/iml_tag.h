#ifndef __iml_tag_h
#define __iml_tag_h

#include "iml_tag_base.h"

template <iml_tag_type T>
class iml_tag : public iml_tag_base
{
public:
    iml_tag();
    std::list<double> evaluate() const;
    
};

#include "../src/template/iml_tag.cpp"

#endif