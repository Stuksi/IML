#ifndef __Tokenizer_H
#define __Tokenizer_H

#include <iostream>
#include <string>
#include "../../lib/DLList.h"

enum class TokenType
{
    OpenBracket, // '<'
    CloseBracket, // '>'
    Quote, // '"'
    Slash, // '/'
    Number, // -inf ... inf   
    String, // {'A' ... 'Z'}
    Invalid // '?'
};

struct Token
{
    TokenType type;
    std::string text;
};

class Tokenizer
{
private:
    std::istream& in;

    void clear();
    Token nextToken();

    bool isChar();
    bool isDigit();

    Token readString();
    Token readNumber();
    Token readSign();
public:
    Tokenizer(std::istream&);
    DLList<Token> tokenize();
};

#endif