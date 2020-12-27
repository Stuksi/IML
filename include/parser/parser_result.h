#ifndef __parser_result_h
#define __parser_result_h

#include "../node/node.h"

namespace iml
{
    class parser_result
    {
    private:
        node* root;
    public:
        // Constructor and destructor
        parser_result(node*);
        ~parser_result();

        // Visualization
        void visualize(const char* = "iml_tree.dot");

        // Evaluation
        void evaluate(const char* = "iml_in.iml");
    };
}

#endif