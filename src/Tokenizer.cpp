#include "../include/IML Parsing/Tokenizer.h"

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
    return Token {TokenType::String, text};
}

Token Tokenizer::readNumber()
{
    std::string number = "";
    if (in.peek() == '-')
    {
        number = "-";
        in.get();
    }
    if (in.peek() == '0')
    {
        in.get();
        if (isDigit()) throw;
        number += "0";
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
    return Token {TokenType::Number, number};
}

Token Tokenizer::readSign()
{
    char current = in.get();
    switch (current)
    {
        case '<': return Token {TokenType::OpenBracket, "<"};
        case '>': return Token {TokenType::CloseBracket, ">"};
        case '"': return Token {TokenType::Quote, "\""};
        case '/': return Token {TokenType::Slash, "/"};
        default : return Token {TokenType::Invalid, "" + current};
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
    if (in.peek() == '-' || isDigit())
    {
        return readNumber();
    }
    else if (isChar())
    {
        return readString();
    }
    return readSign();
}

DLList<Token> Tokenizer::tokenize()
{
    DLList<Token> tokenList;
    Token current;
    while (in)
    {
        current = nextToken();
        if (in.eof()) break;
        if (current.type == TokenType::Invalid) throw;
        tokenList.append(current);
    }
    return tokenList;
}