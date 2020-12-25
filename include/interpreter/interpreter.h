#ifndef __interpreter_h
#define __interpreter_h

#include "../reader/reader.h"
#include "../tag/tag.h"
#include <stack>
#include <unordered_map>

namespace iml
{
    typedef std::stack<tag*> hierarchy;
    typedef std::stack<std::list<double>> hierarchy_values;
    typedef std::unordered_map<std::string, std::stack<std::list<double>>> attribute_links;

    class interpreter
    {
    private:
        reader reader_;
        hierarchy hierarchy_;
        hierarchy_values values_;
        attribute_links links_;
        
        // bool is_body_expression();
        void evaluate_value();
        void evaluate_tag_expression();
        // void evaluate_body_expression();
        void evaluate_expression();
    public:
        std::list<double> evaluate(std::istream&);
    };
}

#endif