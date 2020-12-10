#ifndef __iml_tag_h
#define __iml_tag_h

#include "iml_attribute.h"
#include <list>

enum class iml_tag_type
{
    iml_root,
    map_inc,
    let
};

class iml_tag
{
protected:
    iml_tag_type tag_type;
    std::list<double> values;
public: 
    iml_tag_type type() const;

    void set_values(std::list<double>);
    void add_value(double);
    void add_values(std::list<double>);

    virtual void set_attribute(iml_attribute);
    virtual iml_attribute get_attribute() const;
    virtual std::list<double> eval() = 0;
};

#endif