#ifndef __tag_h
#define __tag_h

#include "attribute.h"
#include "tag_type.h"

namespace iml
{
    class tag
    {
    private:
        tag_type type;
    public:
        // Constructors and destructor
        tag();
        tag(tag_type);
        virtual ~tag();

        // Accessors and mutators
        tag_type get_type() const;
        std::string as_string() const;
        virtual attribute get_attribute() const;
        virtual void set_attribute();
    };   
} 

#endif