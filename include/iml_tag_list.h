#ifndef __iml_tag_list_h
#define __iml_tag_list_h

#include "iml_tag_attribute.h"

// =============================================== // ATTRIBUTE TAGS // =============================================== //

class iml_map_inc : public iml_tag_attribute
{
public:
    iml_map_inc();
    void set_attribute(iml_attribute);
    std::list<double> eval();
};

class iml_let : public iml_tag_attribute
{
public:
    iml_let();
    void set_attribute(iml_attribute);
    std::list<double> eval();
};

// ================================================================================================================== //

// =============================================== // NON ATTRIBUTE TAGS // =============================================== //



// ================================================================================================================== //

#endif