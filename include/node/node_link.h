#ifndef __node_link_h
#define __node_link_h

#include "node.h"

namespace iml
{
    /// Node representing the attribute to expression link.
    class node_link : public node
    {
    private:
        std::string name;
    public:
        //! Default constructor of class node_link. Initializes the class value with a non-empty name (upper-case string).
        node_link(std::string);

        //! Visualizes the node by creating a visual tree node with the link name in it and visualizes the children. 
        void visualize(std::ostream&) const;
        //! Evaluates the node, by evaluating the node's chuldren, storing the results in a list and returning it.
        std::list<double> evaluate() const;
    };
}

#endif