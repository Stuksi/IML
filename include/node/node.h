#ifndef __node_h
#define __node_h

#include "../tag/tag.h"
#include <iostream>
#include <list>

namespace iml
{
    /// Base class of the tree nodes.
    class node
    {
    private:
        node* parent;
        std::list<node*> children;
    public:
        //! Default constructor of class node. Initializes the node parameters with null objects.
        node();
        //! Destroys the children of the node. 
        virtual ~node();

        //! Sets node parent.
        void set_parent(node*);
        //! Sets node children.
        void set_children(std::list<node*>);
        //! Sets node link.
        virtual void set_link(node*);

        //! Gets node parent (or nullptr if the node is the document root).
        node* get_parent() const;
        //! Gets the list of children of the node (if it is a leaf node).
        std::list<node*> get_children() const;
        //! Gets the tag associated with the node (or nullptr if the node does not support tags).
        virtual tag* get_tag() const;
        //! Gets the attribute-link expression (or nullptr if the node does not support links).
        virtual node* get_link() const; 

        //! Visualizes the node depending on the type.
        virtual void visualize(std::ostream&) const = 0;
        //! Evaluates the node depending on the type.
        virtual std::list<double> evaluate() const = 0;
    };
}

#endif