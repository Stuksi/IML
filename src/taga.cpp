#include "../include/tag/taga.h"

namespace iml
{
    taga::taga(tag_type _type, attribute _attr) : tag(_type), attr(_attr)
    {}

    attribute taga::get_attribute() const
    {
        return attr;
    }

    void taga::set_attribute(attribute _attr)
    {
        attr = _attr;
    }
}