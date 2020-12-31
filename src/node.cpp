#include "../include/node/node.h"

namespace iml
{
    node::node() : parent(nullptr)
    {}

    node::~node()
    {
        for (node*& child : children)
        {
            delete child;
        }
    }

    void node::set_parent(node* _parent)
    {
        parent = _parent;
    }

    void node::set_children(std::list<node*> _children)
    {
        children = _children;
    }

    void node::set_link(node* _link)
    {}

    node* node::get_parent() const
    {
        return parent;
    }

    std::list<node*> node::get_children() const
    {
        return children;
    }

    tag* node::get_tag() const
    {
        return nullptr;
    }

    node* node::get_link() const
    {
        return nullptr;
    }
}
