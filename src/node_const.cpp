// #include "../include/node/node_const.h"

// namespace iml
// {
//     node_const::node_const() : node(node_type_const), value_(0)
//     {}

//     node_const::node_const(std::string value) : node(node_type_const)
//     {
//         try
//         {
//             value_ = stod(value);
//         }
//         catch(...)
//         {
//             value_ = 0;
//         }
//     }
    
//     node_const::~node_const()
//     {}
    
//     void node_const::visualize(std::ostream& out) const
//     {
//         out << (long)this << "[label=\"" << value_ << "\"];\n";
//     }
    
//     std::list<double> node_const::evaluate() const
//     {
//         return {value_};
//     }
// }