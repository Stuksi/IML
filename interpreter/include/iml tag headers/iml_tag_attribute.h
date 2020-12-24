#ifndef __iml_attribute_h
#define __iml_attribute_h

#include <string>

class iml_tag_attribute
{
private:
    std::string text_;
public:
    iml_tag_attribute(std::string);
    std::string text() const;
    bool empty() const;
};

#endif