#ifndef __Atribute_H
#define __Atribute_H

#include <vector>
#include <string>

class Attribute
{
private:
    std::string id;
    std::vector<double> values;
public:
    Attribute() = default;
    Attribute(std::string);
    ~Attribute() = default;

    void setId(std::string);
    void setValues(std::vector<double>);

    std::string getId() const;
    std::vector<double> getValues() const;
};

#endif