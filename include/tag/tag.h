#ifndef __tag_h
#define __tag_h

#include "attribute.h"
#include "tag_type.h"

namespace iml
{
    /// Base tag class.
    class tag
    {
    private:
        tag_type type;
    public:
        //! Default constructor of class tag. Initializes the tag as a null-tag.
        tag();
        //! Parameterized constructor of class tag. Initializes the tag with the passed type.
        tag(tag_type);

        // Gets the tag type.
        tag_type get_type() const;
        // Gets the tag type as a string.
        std::string as_string() const;
        // Gets the tag attribute (if the tag does not support attributes an error message is displayed).
        virtual attribute get_attribute() const;
        
        // Sets the tag attribute (if the tag does not support attributes an error message is displayed).
        virtual void set_attribute(attribute);
    };   
} 

#endif