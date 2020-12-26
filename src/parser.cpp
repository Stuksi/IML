// #include "../include/parser/parser.h"
// #include "../include/node/node_const.h"
// #include "../include/node/node_tag.h"
// #include <cassert>

// namespace iml
// {
//     parser::parser(std::istream& in) : reader_(in)
//     {}

//     node* parser::parse()
//     {
//         if (reader_.current().type == token_number)
//         {
//             std::string text = reader_.current().text;
//             reader_.next();
//             return new node_const(text);
//         }
        
//         tag* open_tag = reader_.read_open_tag();        
    
//         std::list<node*> children;
//         while (!reader_.end())
//         {
//             children.push_back(parse());
//         }

//         tag* close_tag = reader_.read_close_tag();

//         assert(open_tag->type() == close_tag->type());

//         return new node_tag(open_tag, children);
//     }

//     parser_result parser::build_tree()
//     {
//         return parser_result {parse()};
//     }
// }