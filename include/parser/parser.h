#ifndef __parser_h
#define __parser_h

#include "parser_result.h"
#include "../reader/reader.h"

namespace iml
{
    class parser
    {
        reader r;
        node* parse();
    public:
        // Construct tree
        parser_result build_tree(const char*);
    };
}

#endif