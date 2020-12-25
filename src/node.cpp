#include "../include/node/node.h"

namespace iml
{
    node::node() : type_(node_null)
    {}

    node::node(node_type type) : type_(type)
    {}

    node::~node()
    {}

    node_type node::type() const
    {
        return type_;
    }

    // node_iterator node::begin()
    // {
    //     return node_iterator((node*&)*this);
    // }

    // node_iterator node::end()
    // {
    //     return node_iterator((node*&)*this);
    // }
}
