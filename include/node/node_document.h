#ifndef __node_document_h
#define __node_document_h

#include "node.h"

namespace iml
{
    /// @brief Root node of the document.
    ///
    /// The root of the tree (does not have a parent).
    class node_document : public node
    {
    public:
        //! Visualizes the node by creating a visual tree node with 'ROOT' in it and visualizes the children. 
        void visualize(std::ostream&) const;
        //! Evaluates the node, by evaluating the node's chuldren, storing the results in a list and returning it.
        std::list<double> evaluate() const;
    };
}

#endif