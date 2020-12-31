#include "../include/node/node_const.h"

namespace iml
{
    node_const::node_const(std::string _value) : value(_value)
    {}
    
    void node_const::visualize(std::ostream& out) const
    {
        out << (long)this << "[label=\"" << value << "\"];\n";
    }
    
    std::list<double> node_const::evaluate() const
    {
        if (isdigit(value[0]) || value[0] == '-')
        {
            return {stod(value)};
        }
        node* parent = get_parent();
        while (parent && parent->get_tag()->get_attribute().get_value() != value)
        {
            parent = parent->get_parent();
        }
        if (parent == nullptr)
        {
            throw std::runtime_error(value + " is not defined!");
        }
        return parent->get_link() == nullptr ? std::list<double>() : parent->get_link()->evaluate();
    }
}