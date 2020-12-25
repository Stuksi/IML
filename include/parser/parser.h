#ifndef __parser_h
#define __parser_h

#include "parser_result.h"
#include "../reader/reader.h"

namespace iml
{
    class parser
    {
        reader reader_;
        
        node* parse();
    public:
        parser(std::istream&);
        parser_result build_tree();
    };
}

#endif