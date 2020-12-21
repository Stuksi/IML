#ifndef __iml_factory_h
#define __iml_factory_h

#include "iml_tag_base.h"

class iml_factory
{
public:
    static bool exists(std::string);
    static iml_tag_base* to_tag(std::string);
    static iml_tag_base* to_atag(std::string, iml_attribute);
    static iml_tag_type to_type(std::string);
    static std::string to_string(iml_tag_type);
};

#endif