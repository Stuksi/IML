#ifndef __taga_h
#define __taga_h

#include "tag.h"

namespace iml
{
    class taga : public tag
    {
    private:
        attribute attr;
    public:
        // Constructors
        taga(tag_type, attribute);

        // Accessors and mutatos
        attribute get_attribute() const;
        void set_attribute(attribute);
    };
}

#endif