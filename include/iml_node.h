#ifndef __NODE_H
#define __NODE_H

struct iml_node_struct
{
    iml_node_struct *parent;
    iml_node_struct *first_child;
    iml_node_struct *last_child;
    iml_node_struct *sibling;
};

class iml_node
{    
private:
    iml_node_struct *root;
public:
    iml_node();
    iml_node(iml_node_struct*);
    ~iml_node();

    iml_node parent() const;
    iml_node first_child() const;
    iml_node next_sibling() const;
};

#endif