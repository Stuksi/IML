#ifndef __IML_ATTRIBUTE_H
#define __IML_ATTRIBUTE_H

#include "iml_node.h"

enum iml_attribute_type
{
    none,
    number,
    string,
    list
};

class iml_attribute
{
private:
    iml_attribute_type _type;
public:
    iml_attribute(iml_attribute_type = none);
    iml_attribute_type type() const;
};

class iml_attribute_alphanumeric : public iml_attribute
{
private:
    char* _value;
public:
    iml_attribute_alphanumeric(char*);
    ~iml_attribute_alphanumeric();
    char* value();
};

class iml_attribute_list : public iml_attribute
{
private:
    char* _name;
    iml_node *root;
public:
    iml_attribute_list(char*);
    ~iml_attribute_list();
};

#endif