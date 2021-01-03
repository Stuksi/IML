#ifndef __parser_result_h
#define __parser_result_h

#include "../node/node.h"

namespace iml
{
    /// @brief User handle.
    ///
    /// A wrap of the parsed tree for users to use and configure. 
    class parser_result
    {
    private:
        node* root;
    public:
        //! Parameterized constructor of class parser_result. Initializes the root of the tree.
        parser_result(node*);
        //! Destroys the tree.
        ~parser_result();

        //! Visualizes the tree by calling the root visualize method.
        void visualize(const char* = "iml_tree.dot");

        //! Evaluates the tree by calling the root evaluate method.
        void evaluate(const char* = "iml_result.imlr");
    };
}

#endif