#ifndef __factory_h
#define __factory_h

#include "tag.h"

namespace iml
{
    /// Tag factory.
    class factory
    {
    public:
        //! Converts a string (type), to a tag (with an attribute if the tag type supports it).
        static tag* to_tag(std::string, attribute = attribute());
    };
}

#endif