#ifndef __iml_interpreter_h
#define __iml_interpreter_h

#include "iml_parser.h"

typedef std::stack<tag> iml_hierarchy;

class iml_interpreter
{
private:
    iml_parser* parser_;
    iml_hierarchy hierarchy_;
    iml_name_links links_;
    bool is_body_expression();
    void evaluate_value();
    void evaluate_tag_expression();
    void evaluate_body_expression();
    void evaluate_expression();
public:
    std::list<double> evaluate(std::istream&);
};

#endif