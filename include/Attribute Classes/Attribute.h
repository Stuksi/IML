#ifndef __Atribute_H
#define __Atribute_H

#include <string>
#include "../../lib/DLList.h"

class Attribute
{
private:
    std::string id;
public:
    Attribute() = default;
    Attribute(std::string);

    void setId(std::string);
    std::string getId() const;
};

#endif