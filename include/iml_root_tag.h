#ifndef __iml_root_tag_h
#define __iml_root_tag_h

#include "iml_tag.h"

class iml_root_tag : public iml_tag
{
public:
    iml_root_tag();
    std::list<double> eval();
};

#endif