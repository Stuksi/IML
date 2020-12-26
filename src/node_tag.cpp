// #include "../include/node/node_tag.h"
// #include "../include/tag/tag_apply.h"

// namespace iml
// {
//     node_tag::node_tag() : tag_(nullptr), children_(std::list<node*>())
//     {}

//     node_tag::node_tag(tag* tag, std::list<node*> children) : tag_(tag), children_(children)
//     {}

//     node_tag::~node_tag()
//     {
//         for (node*& child : children_)
//         {
//             delete child;
//         }
//     }

//     void node_tag::visualize(std::ostream& out) const
//     {
//         out << (long)this << "[label=\"" << "Tag: " << tag_->as_string() << "\"];\n";
//         for (node* child : children_)
//         {
//             out << (long)this << "->" << (long)child << ";\n";
//             child->visualize(out);
//         }
//     }

//     std::list<double> node_tag::evaluate() const
//     {
//         std::list<double> values;
//         for (node* child : children_)
//         {
//             for (double value : child->evaluate())
//             {
//                 values.push_back(value);
//             }
//         }
//         return tag_apply::apply(values, tag_);
//     }
// }