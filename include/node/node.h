#ifndef __node_h
#define __node_h

#include "node_type.h"
// #include "node_iterator.h"
#include <iostream>
#include <list>

namespace iml
{
    class node
    {
    private:
        node_type type_;
    public:
        node();
        node(node_type);
        virtual ~node();

        node_type type() const;

        // node_iterator begin();
        // node_iterator end();
 
        virtual void visualize(std::ostream&) const = 0;
        virtual std::list<double> evaluate() const = 0;
    };
}

#endif