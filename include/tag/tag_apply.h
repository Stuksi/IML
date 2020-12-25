#ifndef __tag_apply_h
#define __tag_apply_h

#include "tag.h"
#include <list>

namespace iml
{
    class tag_apply
    {
        template <tag_type T>
        static std::list<double> apply(std::list<double>);
    public:
        static std::list<double> apply(std::list<double>, tag*);
    };

    template <tag_type T>
    std::list<double> tag_apply::apply(std::list<double> values)
    {
        return std::list<double>();
    }
}

#endif