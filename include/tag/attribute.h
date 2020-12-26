#ifndef __attribute_h
#define __attribute_h

#include <string>

namespace iml
{
    class attribute
    {
    private:
        std::string value;
    public:
        // Constructors
        attribute();
        attribute(std::string);

        // Accessors and mutators
        std::string get_value() const;
        double as_double(double = 0) const;
        int as_int(int = 0) const;
        void set_value(std::string);
        void set_value(double);

        // Predicates
        bool empty() const;
    };
}

#endif