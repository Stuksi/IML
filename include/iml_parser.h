#ifndef __iml_parser_h
#define __iml_parser_h

#include "iml_tokenizer.h"
#include "iml_tag.h"
#include <stack>
#include <unordered_map>

typedef std::unordered_map<std::string, std::stack<std::list<double>>> indentificator_links;

class iml_parser
{
private:
    // Core
    std::list<iml_token> t_list;
    std::list<iml_token>::iterator t_list_iterator;
    std::stack<iml_tag*> hierarchy;
    indentificator_links linked_names;
    
    // Selectors and Iterators
    void next();
    void previous();
    iml_token current();

    // Predicates
    bool end_expression();
    bool is_value();

    // Atoms
    void parse_token(iml_token_type);
    void parse_value();
    void parse_open_tag();
    void parse_body_tag();
    void parse_close_tag();
    void parse_attribute();

    // Expressions
    void parse_expression();
    void parse_tag_expression();
    
public:
    void build(std::istream&, std::ostream&);
};

#endif