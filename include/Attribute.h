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
public:
    Attribute();
    Attribute(const char*);

    void setId(const char*);
    void setType(AttributeType);

    std::string getId() const;
    AttributeType getType() const;
};

class ListAttribute : public Attribute
{
private:
    std::vector<double> values;
public:
    ListAttribute(const char*, const std::vector<double>&);
    ~ListAttribute();

    std::vector<double> getValues() const;
};


#endif