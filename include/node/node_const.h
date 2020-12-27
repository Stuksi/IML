#ifndef __node_const_h
#define __node_const_h

#include "node.h"
#include <string>

namespace iml
{
    class node_const : public node
    {
    private:
        double value;
    public:
        // Constructor
        node_const(std::string);
        
        void visualize(std::ostream&) const;
        std::list<double> evaluate() const;
    };
}

#endif