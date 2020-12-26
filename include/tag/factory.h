#ifndef __factory_h
#define __factory_h

#include "tag.h"

namespace iml
{
    class factory
    {
    public:
        // Tag creation
        static tag* to_tag(std::string, attribute = attribute());
    };
}

#endif