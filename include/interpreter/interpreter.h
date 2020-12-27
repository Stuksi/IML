#ifndef __interpreter_h
#define __interpreter_h

#include "../reader/reader.h"
#include "../tag/tag.h"
#include <stack>
#include <unordered_map>

namespace iml
{
    typedef std::stack<tag*> tag_hierarchy;
    typedef std::stack<std::list<double>> values_hierarchy;
    typedef std::unordered_map<std::string, std::stack<std::list<double>>> name_links;

    class interpreter
    {
    private:
        reader r;
        tag_hierarchy tags;
        values_hierarchy values;
        name_links links;
        
        bool is_body_expr();

        void value_expr();
        void tag_expr();
        void body_expr();
        void expr();

        std::list<double> evaluate();
        void interpret(const char*);
    public: 
        // Interpretation
        void interpret_file(const char*, const char* = "iml_result.imlr");
        void interpret_stream(std::istream&, const char* = "iml_result.imlr");
        void interpret_buffer(const char*, const char* = "iml_result.imlr");
    };
}

#endif