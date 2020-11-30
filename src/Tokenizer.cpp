#include "../include/Tokenizer.h"

Tokenizer::Tokenizer(std::istream& _in) : in(_in)
{}

bool Tokenizer::isChar()
{
    return (in.peek() >= 'A' && in.peek() <= 'Z') || in.peek() == '-';
}

bool Tokenizer::isDigit()
{
    return in.peek() >= '0' && in.peek() <= '9';
}

bool Tokenizer::isSign()
{
    return in.peek() == '<' || in.peek() == '>' || in.peek() == '"' || in.peek() == '/';
}

Token Tokenizer::readString()
{
    std::string text = "";
    while (isChar())
    {
        text += in.get();
    }
    return Token {String, text};
}

Token Tokenizer::readNumber()
{
    int negative = 1;
    std::string number = "";
    if (in.peek() == '-')
    {
        negative = -1;
    }
    if (in.peek() == '0')
    {
        in.get();
        if (isDigit()) throw;
        number = "0";
    } else {
        while (isDigit())
        {
            number += in.get();
        }
    }
    if (in.peek() == '.')
    {
        number += in.get();
        if (!isDigit()) throw;
        while (isDigit())
        {
            number += in.get();
        }
    }
    return Token {Number, number};
}

Token Tokenizer::readSign()
{
    switch (in.get())
    {
    case '<': return Token {OpenBracket, "<"};
    case '>': return Token {CloseBracket, ">"};
    case '"': return Token {Quote, "\""};
    case '/': return Token {Slash, "/"};
    }
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
    if (isSign())
    {
        return readSign();
    }
    else if (isDigit() || in.peek() == '-')
    {
        return readNumber();
    }
    else if (isChar())
    {
        return readString();
    }
    throw;
}

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokenized;
    while ((bool)in)
    {
        tokenized.push_back(nextToken());
    }
    return tokenized;
}