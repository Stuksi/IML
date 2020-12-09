#ifndef __iml_factory_h
#define __iml_factory_h

#include "iml_tag.h"

class iml_factory
{
public:
    static iml_tag* stotag(std::string);
    static iml_tag_type stotype(std::string);
};

#endif