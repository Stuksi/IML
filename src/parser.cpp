#include "../include/parser/parser.h"
#include "../include/node/node_const.h"
#include "../include/node/node_tag.h"
#include "../include/node/node_document.h"
#include <fstream>

namespace iml
{
    node* parser::parse()
    {
        if (r.current().type == token_number)
        {
            std::string text = r.current().text;
            r.next();
            return new node_const(text);
        }
        
        tag* open_tag = r.read_open_tag();        
    
        std::list<node*> children;
        while (!r.is_end())
        {
            children.push_back(parse());
        }

        tag* close_tag = r.read_close_tag();

        if (open_tag->get_type() != close_tag->get_type()) throw std::runtime_error("Wrong closing tag for - " + open_tag->as_string() + ". Given - " + close_tag->as_string() + "!");

        return new node_tag(open_tag, children);
    }

    parser_result parser::build_tree(const char* input_path)
    {
        std::ifstream in(input_path);
        r = reader(in);
        std::list<node*> document_children;
        try
        {
            while (!r.is_end())
            {
                document_children.push_back(parse());
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Error -> " << e.what() << std::endl;
            std::cout << "Parsing failed!" << std::endl;
            return parser_result(new node_document(std::list<node*>()));
        }
        std::cout << "Parsing successfull!" << std::endl;
        return parser_result(new node_document(document_children));
    }
}