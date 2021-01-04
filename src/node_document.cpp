#include "../include/node/node_document.h"
#include "../include/tag/tag_config.h"

namespace iml
{
    void node_document::visualize(std::ostream& out) const
    {
        out << (long)this << "[label=\"ROOT\"];\n";
        for (node* child : get_children())
        {
            out << (long)this << "->" << (long)child << ";\n";
            child->visualize(out);
        }
    }

    std::list<double> node_document::evaluate() const
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

    void node_document::save(std::ostream& out) const
    {
        for (node* child : get_children())
        {
            child->save(out);
        }        
    }
}