#ifndef __reader_h
#define __reader_h

#include "../token/lexer_result.h"
#include "../tag/tag.h"
#include <iostream>

namespace iml
{
    /// Reader class, validating the expressions based on the iml grammar.
    ///
    /// Helper class used to read and validate expressions and check for future expressions.
    class reader
    {
    private:
        lexer_result tokens;

        //! Reads an exprected token type.
        void read_token(token_type);
    public: 
        //! Default constructor of class reader (not used).
        reader() = default;
        //! Default constructor of class reader. Initializes the tokens by calling a lexer class.
        reader(std::istream&);

        //! Gets the currently pointed token in the tokens list.
        token current() const;
        //! Points to the next token in the tokens list.
        void next();
        //! Points to the previous token in the tokens list.
        void previous();
        
        //! Checks if it is an 'end' tag (BODY or close tag) or end of the input.
        bool is_end();
        //! Checks if the currently pointed token is of a value type (string or number).
        bool is_value();

        //! Reads and returns an open tag based on the iml grammar.
        tag* read_open_tag();
        //! Reads and returns a close tag based on the iml grammar.
        tag* read_close_tag();
        //! Reads and returns a body tag based on the iml grammar.
        tag* read_body_tag();
        //! Reads and returns an attribute based on the iml grammar.
        attribute read_attribute();
    };
}


#endif