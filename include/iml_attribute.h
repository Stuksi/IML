#ifndef __iml_attribute_h
#define __iml_attribute_h

#include <string>

class iml_attribute
{
private:
    std::string info;
public:
    iml_attribute() = default;
    iml_attribute(std::string);
    
    void set(std::string);
    std::string get() const;
};

#endif