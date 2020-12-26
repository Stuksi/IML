#include "../include/tag/attribute.h"

namespace iml
{
    attribute::attribute() : value("")
    {}

    attribute::attribute(std::string _value) : value(_value)
    {}


    std::string attribute::get_value() const
    {
        return value;
    }

    double attribute::as_double(double def) const
    {
        double _value;
        try
        {
            _value = stod(value);
        }
        catch(...)
        {
            _value = def;
        }
        return _value;
    }

    int attribute::as_int(int def) const
    {
        double _value;
        try
        {
            _value = stod(value);
        }
        catch(...)
        {
            _value = def;
        }
        return _value;
    }

    void attribute::set_value(std::string _value)
    {
        value = _value;
    }

    void attribute::set_value(double _value)
    {
        value = std::to_string(_value);
    }

    bool attribute::empty() const
    {
        return value == "";
    }
}