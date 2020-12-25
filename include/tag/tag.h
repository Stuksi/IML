#ifndef __tag_h
#define __tag_h

#include "attribute.h"
#include "tag_type.h"

namespace iml
{
    class tag
    {
    private:
        tag_type type_;
    public:
        tag();
        tag(tag_type);
        virtual ~tag();

        tag_type type() const;
        std::string as_string() const;

        virtual attribute attr() const;
    };   
} 

#endif