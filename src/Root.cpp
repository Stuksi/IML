#include "../include/IML Tags/Root.h"

Root::Root()
{
    setType(TagType::ROOT);
}

std::vector<double> Root::eval() const
{
    return getValues();
}