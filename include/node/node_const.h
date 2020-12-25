#ifndef __node_const_h
#define __node_const_h

#include "node.h"
#include <string>

namespace iml
{
    class node_const : public node
    {
    private:
        double value_;
    public:
        node_const();
        node_const(std::string);
        ~node_const();
        
        void visualize(std::ostream&) const;
        std::list<double> evaluate() const;
    };
}

#endif