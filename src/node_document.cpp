#include "../include/node/node_document.h"
#include "../include/tag/tag_config.h"

namespace iml
{
    node_document::node_document(std::list<node*> _children) : children(_children)
    {}

    node_document::~node_document()
    {
        for (node*& child : children)
        {
            delete child;
        }
    }

    void node_document::visualize(std::ostream& out) const
    {
        out << (long)this << "[label=\"ROOT\"];\n";
        for (node* child : children)
        {
            out << (long)this << "->" << (long)child << ";\n";
            child->visualize(out);
        }
    }

    std::list<double> node_document::evaluate() const
    {
        std::list<double> values;
        for (node* child : children)
        {
            for (double value : child->evaluate())
            {
                values.push_back(value);
            }
        }
        return tag_config::apply(values);
    }
}