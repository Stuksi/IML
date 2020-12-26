#include "../include/node/node.h"

namespace iml
{
    node::node() : type_(node_type_null)
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
    //     return node_iterator((node*&)*this, false);
    // }

    // node_iterator node::end()
    // {
    //     return node_iterator((node*&)*this, true);
    // }

    node*& node::node_ptr() const
    {
        return (node*&)*this;
    }

    std::string node::as_string() const
    {
        if (type_ == node_type_document)
        {
            return "ROOT";
        }
        else if (type_ == node_type_const)
        {
            return "";
        } 
        return "";
    }
}
