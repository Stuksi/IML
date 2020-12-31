#include "../include/node/node_tag.h"
#include "../include/tag/tag_config.h"

namespace iml
{
    node_tag::node_tag(tag* tag) : current_tag(tag), link(nullptr)
    {}

    node_tag::~node_tag()
    {
        delete current_tag;
        delete link;
    }

    void node_tag::set_link(node* _link)
    {
        link = _link;
    }

    tag* node_tag::get_tag() const
    {
        return current_tag;
    }

    node* node_tag::get_link() const
    {
        return link;
    } 

    void node_tag::visualize(std::ostream& out) const
    {
        std::string attr;
        try
        {
            attr = current_tag->get_attribute().get_value();
        }
        catch(const std::exception& e)
        {
            attr = "";
        }
        out << (long)this << "[label=\"" << "Tag: " << current_tag->as_string();
        if (attr != "")
        {
             out << " Attribute: " << attr;
        }
        out << "\"];\n";
        if (link != nullptr)
        {
            link->visualize(out);
            out << (long)this << "->" << (long)link << ";\n";
        }
        for (node* child : get_children())
        {
            out << (long)this << "->" << (long)child << ";\n";
            child->visualize(out);
        }
    }

    std::list<double> node_tag::evaluate() const
    {
        std::list<double> values;
        for (node* child : get_children())
        {
            for (double value : child->evaluate())
            {
                values.push_back(value);
            }
        }
        return tag_config::apply(values, current_tag);
    }
}