#ifndef __attribute_h
#define __attribute_h

#include <string>

namespace iml
{
    /// Attribute of tags.
    class attribute
    {
    private:
        std::string value;
    public:
        //! Default constructor of class attribute. Initializes the class value with an empty string.
        attribute();
        //! Parameterized constructor of class attribute. Initializes the class value with the passed string.
        attribute(std::string);

        //! Gets the attribute value.
        std::string get_value() const;
        //! Gets the attribute value, converted to a double (or the default value if a conversion is not possible).
        double as_double(double = 0) const;
        //! Gets the attribute value, converted to an integer (or the default value if a conversion is not possible).
        int as_int(int = 0) const;

        //! Sets the attribute value.
        void set_value(std::string);
        //! Sets the attribute value with type convertion.
        void set_value(double);

        //! Checks if the attribute is empty (i.e. if the value is an empty string).
        bool empty() const;
    };
}

#endif