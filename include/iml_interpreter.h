#ifndef __iml_interpreter_h
#define __iml_interpreter_h

#include "iml_tokenizer.h"
#include "iml_tag_base.h"
#include <stack>
#include <unordered_map>

typedef std::unordered_map<std::string, std::stack<std::list<double>>> indentificator_links;

class iml_interpreter
{
private:
    // Core
    std::list<iml_token> t_list;
    std::list<iml_token>::iterator t_list_iterator;
    std::stack<iml_tag_base*> hierarchy;
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
    void parse_open_tag();
    void parse_body_tag();
    void parse_close_tag();
    iml_attribute parse_attribute();

    // Expressions
    void evaluate_expression();
    void evaluate_value();
    void evaluate_tag_expression();
    void evaluate_body_expression();
    
public:
    void build(std::istream&, std::ostream&);
};

#endif