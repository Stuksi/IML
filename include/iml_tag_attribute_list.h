#ifndef __iml_tag_attribute_list_h
#define __iml_tag_attribute_list_h

#include "iml_tag_attribute.h"

class iml_map_inc : public iml_tag_attribute
{
public:
    iml_map_inc();
    dllist<double> eval();
    void set_attribute(iml_attribute);
};

class iml_let : public iml_tag_attribute
{
public:
    iml_let();
    dllist<double> eval();
    void set_attribute(iml_attribute);
};

#endif