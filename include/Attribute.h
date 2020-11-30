#ifndef __Atribute_H
#define __Atribute_H

#include <vector>
#include <string>

enum AttributeType
{
    Empty,
    AlphaNumeric,
    List
};

class Attribute
{
private:
    AttributeType type;
    std::string id;
    std::vector<double> values;
public:
    Attribute();

    void setType(AttributeType);
    void setId(std::string);
    void setValues(std::vector<double>);

    AttributeType getType() const;
    std::string getId() const;
    std::vector<double> getValues() const;
};

#endif