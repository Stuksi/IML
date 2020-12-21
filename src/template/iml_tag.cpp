#ifndef __iml_tag_cpp
#define __iml_tag_cpp

#include "../../include/iml_tag.h"

template <iml_tag_type T>
iml_tag<T>::iml_tag() : iml_tag_base(T)
{}

template <>
std::list<double> iml_tag<iml_tag_type::iml_root>::evaluate() const
{
    return values();
}

#endif