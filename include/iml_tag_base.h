#ifndef __iml_tag_base_h
#define __iml_tag_base_h

#include "iml_attribute.h"
#include <list>

enum class iml_tag_type
{
    iml_root,
    map_inc,
    let
};

class iml_tag_base
{
private:
    iml_tag_type type_;
    std::list<double> values_;

public:
    iml_tag_base() = default;
    iml_tag_base(iml_tag_type);
    virtual ~iml_tag_base() = default;

    iml_tag_type type() const;
    std::list<double> values() const;
    
    void add(std::list<double>);
    void add(double);
    void clear();

    virtual iml_attribute attribute() const;
    virtual std::list<double> eval() const = 0;

};

#endif