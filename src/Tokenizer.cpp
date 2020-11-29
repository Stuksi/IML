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
        return Token {Open, "<", -1};
    }
    else if (cursor == '>')
    {
        return Token {Close, ">", -1};
    }
    else if (isNumber())
    {
        return Token {Number, "?", readNumber()};
    }
    else if (isText())
    {
        return Token {Text, readText(), -1};
    }
    else if (cursor == '/')
    {
        return Token {Slash, "/", -1};
    }
    else if (cursor == '"')
    {
        return Token {Quote, "\"", -1};
    }
    return Token {Error, "?", -1};
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

double Tokenizer::readNumber()
{
    double number;
    in >> number;
    return number;
}
