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

        // Get node type
        node_type type() const;

        // Get beginning of tree
        // node_iterator begin();
        // Get end of tree
        // node_iterator end();

        // Get reference to node
        node*& node_ptr() const;

        // Get node as string
        std::string as_string() const;
        
        // Get node children
        // virtual std::list<node*&> children() = 0;
        // Visualize tree node
        virtual void visualize(std::ostream&) const = 0;
        // Evaluate tree node
        virtual std::list<double> evaluate() const = 0;
    };
}

#endif