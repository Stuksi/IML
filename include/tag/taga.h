#ifndef __taga_h
#define __taga_h

#include "tag.h"

namespace iml
{
    /// Tag class supporting attributes.
    class taga : public tag
    {
    private:
        attribute attr;
    public:
        //! Default constructor of class taga. Initializes the tag type and the attribute of the tag.
        taga(tag_type, attribute);

        //! Gets the tag attribute.
        attribute get_attribute() const;
        
        //! Sets the tag attribute.
        void set_attribute(attribute);
    };
}

#endif