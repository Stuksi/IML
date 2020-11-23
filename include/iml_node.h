#ifndef __IML_NODE_H
#define __IML_NODE_H

#include "iml_tag.h"

class iml_node
{    
private:
    struct iml_node_struct
    {
        iml_node_struct *parent;
        iml_node_struct *first_child;
        iml_node_struct *next_sibling;
        iml_tag *tag;
    };

    iml_node_struct *root;
public:
    iml_node();
    iml_node(iml_node_struct*);
    ~iml_node();

    iml_node parent() const;
    iml_node first_child() const;
    iml_node next_sibling() const;
    iml_tag tag() const;
};

#endif