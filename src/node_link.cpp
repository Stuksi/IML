#include "../include/node/node_link.h"

namespace iml
{
    node_link::node_link(std::string _name) : name(_name)
    {}

    void node_link::visualize(std::ostream& out) const
    {
        out << (long)this << "[label=\"" << "Link: " << name << "\"];\n";
        for (node* child : get_children())
        {
            out << (long)this << "->" << (long)child << ";\n";
            child->visualize(out);
        }
    }

    std::list<double> node_link::evaluate() const
    {
        std::list<double> values;
        for (node* child : get_children())
        {
            for (double value : child->evaluate())
            {
                values.push_back(value);
            }
        }
        return values;
    }
}