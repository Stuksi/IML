#ifndef __attribute_h
#define __attribute_h

#include <string>

namespace iml
{
    class attribute
    {
    private:
        std::string value_;
    public:
        attribute();
        attribute(std::string);

        bool empty() const;
        std::string value() const;
        double as_number() const;
    };
}

#endif