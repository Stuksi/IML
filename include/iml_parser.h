#ifndef __iml_parser_h
#define __iml_parser_h

#include "iml_tokenizer.h"
#include "iml_tag.h"
#include <stack>
#include <unordered_map>

class iml_parser
{
private:
    // Core
    std::stack<iml_tag*> hierarchy;
    std::unordered_map<std::string, std::stack<std::list<double>>> linked_names;
    std::list<iml_token> t_list;
    std::list<iml_token>::iterator t_list_iterator;

    // Predicates
    bool end_expression();
    bool is_value();

    // Selectors and Iterators
    void next();
    void previous();
    iml_token current();

    // Atoms
    void parse_open_tag();
    void parse_body_tag();
    void parse_close_tag();
    void parse_attribute();

    // Expressions
    void parse_expression();
    void parse_tag_expression();
    void parse_value_expression();
    
public:
    void build(std::istream&, std::ostream&);
};

#endif