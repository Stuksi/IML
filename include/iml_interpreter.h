#ifndef __iml_interpreter_h
#define __iml_interpreter_h

#include "iml_tokenizer.h"
#include "iml_tag.h"
#include <stack>
#include <unordered_map>

typedef std::unordered_map<std::string, std::stack<std::list<double>>> indentificator_links;

class iml_interpreter
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
    void evaluate_token(iml_token_type);
    void evaluate_value();
    void evaluate_open_tag();
    void evaluate_body_tag();
    void evaluate_close_tag();
    void evaluate_attribute();

    // Expressions
    void evaluate_expression();
    void evaluate_tag_expression();
    void evaluate_let_tag_expression();
    
public:
    void build(std::istream&, std::ostream&);
};

#endif