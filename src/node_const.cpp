#include "../include/node/node_const.h"

namespace iml
{
    node_const::node_const(std::string _value) : value(stod(_value))
    {}
    
    void node_const::visualize(std::ostream& out) const
    {
        out << (long)this << "[label=\"" << value << "\"];\n";
    }
    
    std::list<double> node_const::evaluate() const
    {
        return {value};
    }
}