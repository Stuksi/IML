#ifndef __factory_h
#define __factory_h

#include "tag.h"

namespace iml
{
    class factory
    {
    public:
        static tag* to_tag(std::string, attribute);
    };
}

#endif