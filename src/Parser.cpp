#include "../include/IML Parsing/Parser.h"
#include "../include/Other/Factory.h"
#include "../include/IML Tags/Root.h"

Parser::Parser(std::istream& in) : tokenList(Tokenizer(in).tokenize()), tokenListIterator(tokenList.begin())
{}

void Parser::next()
{
    ++tokenListIterator;
}

void Parser::previous()
{
    --tokenListIterator;
}

Token Parser::current()
{
    return *tokenListIterator;
}

bool Parser::hasMoreTokens()
{
    return tokenListIterator != tokenList.end();
}

bool Parser::isValue()
{
    return current().type == TokenType::Number || current().type == TokenType::String;
}

bool Parser::isEndTag()
{
    if (current().type == TokenType::OpenBracket)
    {
        next();
        if (current().type == TokenType::Slash || current().text == "BODY")
        {
            previous();
            return true;
        }
        previous();
    }
    return false;
}

void Parser::parseValue()
{
    if (current().type == TokenType::Number)
    {
        hierarchy.top()->addValue(stod(current().text));
    }
    else 
    {   
        hierarchy.top()->addValue(nameLinks[current().text]);
    }
    next();
}

void Parser::parseOpenTag()
{
    if (current().type != TokenType::OpenBracket) throw;
    next();
    if (current().type != TokenType::String) throw;
    Tag *tag = Factory::stringToTag(current().text);
    hierarchy.push(tag);
    next();
    if (current().type == TokenType::Quote)
    {
        parseAttribute();
    }
    if (current().type != TokenType::CloseBracket) throw;
    next();
}

void Parser::parseBodyTag()
{
    if (current().type != TokenType::OpenBracket) throw;
    next();
    if (current().text != "BODY") throw;
    next();
    if (current().type != TokenType::Slash) throw;
    next();
    if (current().type != TokenType::CloseBracket) throw;
    next();
}

void Parser::parseCloseTag()
{
    if (current().type != TokenType::OpenBracket) throw;
    next();
    if (current().type != TokenType::Slash) throw;
    next();
    if (current().type != TokenType::String) throw;
    if (hierarchy.top()->getType() != Factory::stringToTagType(current().text)) throw;
    next();
    if (current().type != TokenType::CloseBracket) throw;
    next();
}

void Parser::parseAttribute()
{
    if (current().type != TokenType::Quote) throw;
    next();
    if (!isValue()) throw;
    Attribute attribute(current().text);
    next();
    if (current().type != TokenType::Quote) throw;
    hierarchy.top()->setAttribute(attribute);
    next();
}

void Parser::parseExpression()
{
    if (!hasMoreTokens() || isEndTag())
    {
        return;
    } 
    else if (isValue())
    {
        parseValue();
    }
    else 
    {
        parseTagExpression();
    }
    parseExpression();
}

void Parser::parseTagExpression()
{
    parseOpenTag();
    parseExpression();
    if (hierarchy.top()->getType() == TagType::LET)
    {
        parseBodyTag();
        nameLinks.insert(hierarchy.top()->getAttribute().getId(), hierarchy.top()->eval());
        hierarchy.top()->setValues(DLList<double>());
        parseExpression();
        nameLinks.erase(hierarchy.top()->getAttribute().getId());
    }
    parseCloseTag();

    DLList<double> values = hierarchy.top()->eval();
    hierarchy.pop();
    hierarchy.top()->addValue(values);
}

void Parser::build(std::ostream& out)
{
    hierarchy.push(new Root());
    try
    {
        parseExpression();
        if (hierarchy.size() != 1) throw;
        out << hierarchy.top()->eval();
    }
    catch(const std::exception& e)
    {
        out << e.what();
    }
}