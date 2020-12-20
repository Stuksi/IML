#ifndef __iml_attribute_h
#define __iml_attribute_h

#include <string>

class iml_attribute
{
private:
    std::string text_;

public:
    iml_attribute() = default;
    iml_attribute(std::string);
    ~iml_attribute() = default;
    
    std::string text() const;
    bool empty() const;
};

#endif