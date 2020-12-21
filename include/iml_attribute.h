#ifndef __iml_attribute_h
#define __iml_attribute_h

#include <string>

class iml_attribute
{
private:
    std::string text_;

public:
    iml_attribute(std::string);
    
    std::string text() const;
    bool empty() const;
    
};

#endif