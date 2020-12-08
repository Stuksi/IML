#ifndef __Root_H
#define __Root_H

#include "../Base Tag Classes/Tag.h"

class Root : public Tag
{
public:
    Root();
    DLList<double> eval() const;
};

#endif