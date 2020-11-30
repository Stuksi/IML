#include "../include/Parser.h"

Parser::Parser(std::istream& in) : tokenized(Tokenizer(in).tokenize()), it(0)
{}

void Parser::next()
{
    it++;
}

void Parser::previous()
{
    it--;
}

Token Parser::current()
{
    return tokenized[it];
}