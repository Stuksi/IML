#include "../include/IML Tags/Root.h"

Root::Root()
{
    type = TagType::ROOT;
}

DLList<double> Root::eval() const
{
    return values;
}