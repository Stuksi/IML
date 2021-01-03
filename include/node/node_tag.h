#ifndef __node_tag_h
#define __node_tag_h

#include "node.h"
#include "../tag/tag.h"

namespace iml
{
    /// Tag nodes, containing a tag (and if the tag type has a body expression, contains a node_link).
    class node_tag : public node
    {
    private:
        tag* current_tag;
        node* link;
    public:
        //! Parameterized constructor of class node_tag. Initializes the tag with a non-null tag.
        node_tag(tag*);
        //! Destroys the tag reference (and link if exists).
        ~node_tag();

        //! Sets node link.
        void set_link(node*);
        
        //! Gets the tag associated with the node.
        tag* get_tag() const;
        //! Gets the attribute-link expression (or nullptr if the node does not contain such parameter).
        node* get_link() const; 

        //! Visualizes the node by creating a visual tree node with the tag type (name) and the children 
        //! (if a link exists, it is the most left child (not associated with the children list)). 
        void visualize(std::ostream&) const;
        //! Evaluates the node, by evaluating the node's chuldren, storing the results in a list 
        //! evaluates the list based on the tag type and returning it.
        std::list<double> evaluate() const;
    };
}

#endif