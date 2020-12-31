#ifndef __lexer_h
#define __lexer_h

#include "lexer_result.h"
#include <iostream>

namespace iml
{
    /// Lexer
    ///
    /// Converts the input signs ,string and numbers to tokens.
    class lexer
    {
    private:
        std::istream& in;

        //! Clears the input white spaces.
        void cws();
        
        //! Returns a sign token (or invalid token if the characters is invalid).
        token next_sign();
        //! Returns a string token (only upper-case string, based on iml grammar).
        token next_string();
        //! Returns a real number token.
        token next_number();
        //! Parses and returns the next token of the stream.
        token next();
    public:
        //! Default constructor of class lexer (not used).
        lexer() = default;
        //! Default constructor of class lexer. Initializes the input stream reference.
        lexer(std::istream&);

        //! Converts (Tokenizes) the input into different types of tokens (if a token is invalid, displays an error message).
        lexer_result tokenize();
    };
}

#endif