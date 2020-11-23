#ifndef __iml_tag_h
#define __iml_tag_h

#include "iml_attribute.h"
#include "../libs/list.h"

enum iml_tag_type {
    MAP_INC,
    MAP_MLT,
    BODY,
    LET
};

class iml_tag
{
private:
    iml_tag_type _type;
    iml_attribute *_attribute;
protected:
    list<char*> lst;
public:
    void add_value(char*);
    iml_attribute* attribute() const;
    iml_tag_type type() const;

    virtual list<double> eval() const = 0;
};

#endif