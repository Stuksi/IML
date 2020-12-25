#include "../include/tag/taga.h"

namespace iml
{
    taga::taga() : attribute_(attribute())
    {}

    taga::taga(tag_type type, attribute attribute) : tag(type), attribute_(attribute)
    {}

    attribute taga::attr() const
    {
        return attribute_;
    }
}