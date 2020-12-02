#include "../include/Tokenizer.h"

Tokenizer::Tokenizer(std::istream& _in) : in(_in)
{}

bool Tokenizer::isChar()
{
    return in.peek() >= 'A' && in.peek() <= 'Z';
}

bool Tokenizer::isDigit()
{
    return in.peek() >= '0' && in.peek() <= '9';
}

Token Tokenizer::readString()
{
    std::string text = "";
    while (isChar() || in.peek() == '-')
    {
        text += in.get();
    }
    return Token {String, text};
}

Token Tokenizer::readNumber()
{
    std::string number = "";
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
    char current = in.get();
    switch (current)
    {
    case '<': return Token {OpenBracket, "<"};
    case '>': return Token {CloseBracket, ">"};
    case '"': return Token {Quote, "\""};
    case '/': return Token {Slash, "/"};
    case '-': return Token {Minus, "-"};
    default : return Token {Invalid, "" + current};
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
    if (isDigit())
    {
        return readNumber();
    }
    else if (isChar())
    {
        return readString();
    }
    return readSign();
}

std::vector<Token> Tokenizer::tokenize()
{
    std::vector<Token> tokenized;
    Token current;
    while (in)
    {
        current = nextToken();
        if (in.eof()) break;
        if (current.type == Invalid) throw;
        tokenized.push_back(current);
    }
    return tokenized;
}