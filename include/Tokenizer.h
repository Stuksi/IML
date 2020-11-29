#ifndef __Tokenizer_H
#define __Tokenizer_H

#include <iostream>
#include <vector>
#include <string>

enum TokenType
{
    Open,
    Close,
    Number,
    Text,
    Slash,
    Quote,
    Error
};

struct Token
{
    TokenType type;
    std::string text;
    double number;
};

class Tokenizer
{
private:
    std::istream& in;

    void clear();
    Token nextToken();

    bool isText();
    std::string readText();
    bool isNumber();
    double readNumber();
public:
    Tokenizer(std::istream&);
    std::vector<Token> tokenize();
};

#endif