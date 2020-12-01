#ifndef __Tokenizer_H
#define __Tokenizer_H

#include <iostream>
#include <vector>
#include <string>

enum TokenType
{
    OpenBracket, // '<'
    CloseBracket, // '>'
    Quote, // '"'
    Slash, // '/'
    Number, // -inf ... inf   
    String, // {'A' ... 'Z'}
    Minus, // '-'
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
    std::vector<Token> tokenize();
};

#endif