#ifndef __lexer_result_h
#define __lexer_result_h

#include "token.h"
#include <list>

namespace iml
{
    /// The result of tokenizing a stream.
    class lexer_result
    {
    public:
        //! Default constructor of class lexer_result (not used).
        lexer_result() = default;
        //! Default constructor of class lexer_result. Initializes the list of tokens by calling the lexer tokenizing method.
        lexer_result(std::list<token>);
        
        std::list<token> tokens;
        std::list<token>::iterator tokens_it;
    };
}

#endif