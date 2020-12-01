#ifndef __Atribute_H
#define __Atribute_H

#include <vector>
#include <string>

enum AttributeType
{
    StringAttribute,
    NumberAttribute
};

class Attribute
{
private:
    std::string id;
    std::vector<double> values;
    AttributeType type;
public:
    Attribute();

    void setId(std::string);
    void setValues(std::vector<double>);
    void setType(AttributeType);

    std::string getId() const;
    std::vector<double> getValues() const;
    AttributeType getType() const;
};

#endif