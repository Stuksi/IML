#ifndef __iml_factory_h
#define __iml_factory_h

#include "iml_tag_base.h"

class iml_factory
{
public:
    static iml_tag_base* stotag(std::string, iml_attribute);
    static iml_tag_type stotype(std::string);
    static std::string typetos(iml_tag_type);
};

#endif