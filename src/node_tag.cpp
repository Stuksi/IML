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
        attribute attr;
        try
        {
            attr = current_tag->get_attribute();
        }
        catch(const std::exception& e)
        {
            attr = attribute();
        }
        out << (long)this << "[label=\"" << "Tag: " << current_tag->as_string();
        if (!attr.empty())
        {
             out << " Attribute: " << attr.get_value();
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

    void node_tag::save(std::ostream& out) const
    {
        out << "\n<" << current_tag->as_string();
        try
        {
            attribute attr = current_tag->get_attribute();
            out << " \"" << attr.get_value() << "\"";
        }
        catch(const std::exception& e)
        {}
        out << "> ";
        if (link != nullptr)
        {
            link->save(out);
        }
        for (node* child : get_children())
        {
            child->save(out);
        }
        out << "</" << current_tag->as_string() << ">\n";
    }
}