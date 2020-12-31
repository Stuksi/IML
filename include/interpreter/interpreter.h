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

    /// The interpreter class evaluates the input and returns the result in an output file.
    ///
    /// Interpreting is done by a straightforward alghorithm, using a stack to store the tag hierarchy,
    /// an unordered_map storing the links between tag attribute names and resulting lists and
    /// another stack containing the hierarchy of lists of values to be modificated and returned as a result.
    class interpreter
    {
    private:
        reader r;
        tag_hierarchy tags;
        values_hierarchy values;
        name_links links;
        
        //! Checks if a body expression follows.
        bool is_body_expr();

        //! Evaluates a value expression. 
        void value_expr();
        //! Evaluates a tag expression.
        void tag_expr();
        //! Evaluates a body expression.
        void body_expr();
        //! Evaluates an expression.
        void expr();

        //! Starts the evaluation process.
        std::list<double> evaluate();
        //! Interprets input (calls the evaluate method).
        void interpret(const char*);
    public: 
        //! Calls interpreter with an input file.
        void interpret_file(const char*, const char* = "iml_result.imlr");
        //! Calls interpreter with an input stream.
        void interpret_stream(std::istream&, const char* = "iml_result.imlr");
        //! Calls interpreter with a string representing the input.
        void interpret_buffer(const char*, const char* = "iml_result.imlr");
    };
}

#endif