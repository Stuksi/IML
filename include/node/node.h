#ifndef __node_h
#define __node_h

#include <iostream>
#include <list>

namespace iml
{
    class node
    {
    public:
        // Destructor
        virtual ~node();

        // Visualize tree node
        virtual void visualize(std::ostream&) const = 0;
        // Evaluate tree node
        virtual std::list<double> evaluate() const = 0;
    };
}

#endif