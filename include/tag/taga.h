#ifndef __taga_h
#define __taga_h

#include "tag.h"

namespace iml
{
    class taga : public tag
    {
    private:
        attribute attribute_;
    public:
        taga();
        taga(tag_type, attribute);

        attribute attr() const;
    };
}

#endif