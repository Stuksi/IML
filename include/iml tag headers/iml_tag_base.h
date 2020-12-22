#ifndef __iml_tag_base_h
#define __iml_tag_base_h

#include "iml_tag_attribute.h"
#include "iml_tag_type.h"
#include <list>

class iml_tag_base
{
private:
    iml_tag_type type_;
    std::list<double> values_;
public:
    iml_tag_base(iml_tag_type);
    iml_tag_type type() const;
    std::list<double> values() const;
    void add(std::list<double>);
    void clear();
    virtual iml_tag_attribute attribute() const;
    virtual std::list<double> evaluate() const = 0;
};

#endif