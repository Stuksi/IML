#include "../include/Parser.h"
#include "../include/Factory.h"

Parser::Parser(std::istream& in) : tokenized(Tokenizer(in).tokenize()), it(0)
{}

void Parser::parse(std::ostream& out)
{
    try
    {
        std::vector<double> parsedResult = parse(new Tag());
        size_t size = parsedResult.size();
        for (size_t i = 0; i < size - 1; i++)
        {
            out << parsedResult[i] << " ";
        }
        out << parsedResult[size - 1];
    }
    catch(const std::exception& e)
    {
        out << e.what();
    }
}

void Parser::get()
{
    it++;
}

Token Parser::peek() const
{
    return tokenized[it];
}

std::vector<double> Parser::parse(Tag* root)
{
    
}