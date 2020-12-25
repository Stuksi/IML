#include "../include/tag/attribute.h"

namespace iml
{
    attribute::attribute() : value_("")
    {}

    attribute::attribute(std::string value) : value_(value)
    {}

    bool attribute::empty() const
    {
        return value_ == "";
    }

    std::string attribute::value() const
    {
        return value_;
    }

    double attribute::as_number() const
    {
        double value;
        try
        {
            value = stod(value_);
        }
        catch(...)
        {
            value = 0;
        }
        return value;
    }
}