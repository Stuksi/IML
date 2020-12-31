#include "../include/parser/parser.h"
#include "../include/node/node_const.h"
#include "../include/node/node_tag.h"
#include "../include/node/node_document.h"
#include "../include/node/node_link.h"
#include <fstream>

namespace iml
{
    node* parser::parse(node* parent)
    {
        if (r.is_value())
        {
            std::string text = r.current().text;
            r.next();
            node* expression_const_node = new node_const(text);
            expression_const_node->set_parent(parent);
            return expression_const_node;
        }
        
        tag* open_tag = r.read_open_tag(); 
        node* expression_node = new node_tag(open_tag);     

        if (open_tag->get_type() == tag_let)
        {
            std::list<node*> link_children;
            while (!r.is_end())
            {
                link_children.push_back(parse(expression_node));
            }
            r.read_body_tag();
            node* link = new node_link(open_tag->get_attribute().get_value());
            link->set_children(link_children);
            link->set_parent(expression_node);
            expression_node->set_link(link);
        }  
    
        std::list<node*> children;
        while (!r.is_end())
        {
            children.push_back(parse(expression_node));
        }
        expression_node->set_children(children);
        expression_node->set_parent(parent);

        tag* close_tag = r.read_close_tag();

        if (open_tag->get_type() != close_tag->get_type()) throw std::runtime_error("Wrong closing tag for - " + open_tag->as_string() + ". Given - " + close_tag->as_string() + "!");

        return expression_node;
    }

    parser_result parser::build_tree(const char* input_path)
    {
        std::ifstream in(input_path);
        r = reader(in);
        node* document_root = new node_document();
        std::list<node*> document_children;
        try
        {
            while (!r.is_end())
            {
                document_children.push_back(parse(document_root));
            }
            document_root->set_children(document_children);
        }
        catch(const std::exception& e)
        {
            std::cout << "Error -> " << e.what() << std::endl;
            std::cout << "Parsing failed!" << std::endl;
            return parser_result(new node_document());
        }
        std::cout << "Parsing successful!" << std::endl;
        return parser_result(document_root);
    }
}