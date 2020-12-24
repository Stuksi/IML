#ifndef __iml_tag_factory_h
#define __iml_tag_factory_h

#include "iml_tag_base.h"

class iml_tag_factory
{
public:
    static bool exists(std::string);
    static iml_tag_base* to_tag(std::string);
    static iml_tag_base* to_atag(std::string, iml_tag_attribute);
};

#endif