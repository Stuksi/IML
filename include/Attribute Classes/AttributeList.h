#ifndef __AttributeList_H
#define __AttributeList_H

#include "Attribute.h"

class AttributeList : public Attribute
{
private:
    std::vector<double> values;
public:
    AttributeList() = default;
    AttributeList(std::string);
    ~AttributeList() = default;
    
    void setValues(std::vector<double>);
    std::vector<double> getValues() const;
};

#endif