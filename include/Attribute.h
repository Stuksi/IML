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
    std::string id;
    AttributeType type;
    std::vector<double> values;
public:
    Attribute();

    void setId(std::string);
    void setType(AttributeType);
    void setValues(std::vector<double>);

    std::string getId() const;
    AttributeType getType() const;
    std::vector<double> getValues() const;
};

#endif