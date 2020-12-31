#ifndef __parser_h
#define __parser_h

#include "parser_result.h"
#include "../reader/reader.h"

namespace iml
{
    /// Main parser class.
    ///
    /// Creates the dom-like tree.
    class parser
    {
        reader r;

        //! Parses the tree based on the iml grammar, and using an argument for parent passing.
        node* parse(node*);
    public:
        //! Construct tree by passing a file path.
        parser_result build_tree(const char*);
    };
}

#endif