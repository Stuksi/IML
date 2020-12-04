#ifndef __Atribute_H
#define __Atribute_H

#include <vector>
#include <string>

class Attribute
{
private:
    std::string id;
public:
    Attribute() = default;
    Attribute(std::string);
    virtual ~Attribute() = default;

    void setId(std::string);
    std::string getId() const;

    virtual void setValues(std::vector<double>);
    virtual std::vector<double> getValues() const;
};

#endif