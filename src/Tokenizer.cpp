#include "../include/Tokenizer.h"

Tokenizer::Tokenizer(std::istream& _in) : in(_in)
{}

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokenized;
    while ((bool)in)
    {
        tokenized.push_back(nextToken());
    }
    return tokenized;
}

void Tokenizer::clear()
{
    while (in.peek() == ' ' || in.peek() == '\n')
    {
        in.get();
    }
}

Token Tokenizer::nextToken()
{
    clear();
    char cursor = in.get();
    if (cursor == '<')
    {
        return Token {Open, "<"};
    }
    else if (cursor == '>')
    {
        return Token {Close, ">"};
    }
    else if (isNumber())
    {
        return Token {Number, readNumber()};
    }
    else if (isText())
    {
        return Token {Text, readText()};
    }
    else if (cursor == '/')
    {
        return Token {Slash, "/"};
    }
    else if (cursor == '"')
    {
        return Token {Quote, "\""};
    }
    return Token {Error, "?"};
}

bool Tokenizer::isText()
{
    return in.peek() >= 'A' && in.peek() <= 'Z';
}

std::string Tokenizer::readText()
{
    std::string text = "";
    while (isText())
    {
        text += in.get();
    }
    return text;
}

bool Tokenizer::isNumber()
{
    return in.peek() >= '0' && in.peek() <= '9';
}

std::string Tokenizer::readNumber()
{
    std::string number = "";
    while (isNumber())
    {
        number += in.get();
    }
    return number;
}
