// #include "../include/node/node_iterator.h"

// namespace iml
// {
//     node_iterator::node_iterator(node*& root, bool end)
//     {
//         if (!end && !node_queue_.empty())
//         {
//             node_queue_.push(root);
//         }
//     }

//     node*& node_iterator::operator*()
//     {
//         return node_queue_.front()->node_ptr();
//     }

//     node_iterator& node_iterator::operator++()
//     {
//         node*& front = node_queue_.front();
//         node_queue_.pop();
//         if (front->type() != node_type_const)
//         {
//             for (node*& child : front->children())
//             {
//                 node_queue_.push(child);
//             }
//         }
//         return *this;
//     }

//     bool node_iterator::operator!=(const node_iterator& iterator)
//     {
//         if (node_queue_.empty())
//         {
//             return !iterator.node_queue_.empty();
//         }
//         return iterator.node_queue_.empty();
//     }
// }