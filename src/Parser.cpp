#include "../include/Parser.h"

Parser::Parser(std::istream& in) : tokenized(Tokenizer(in).tokenize()), it(0), currentTag(new Tag())
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

bool Parser::isCloseTag()
{
    if (current().type == OpenBracket)
    {
        next();
        if (current().type == Slash)
        {
            previous();
            return true;
        }
        previous();
    }
    return false;
}

bool Parser::isBodyTag()
{
    if (current().type == OpenBracket)
    {
        next();
        if (current().text == "BODY")
        {
            previous();
            return true;
        }
        previous();
    }
    return false;
}

void Parser::startTag()
{
    Tag *openTag = parseOpenTag();
    openTag->setParent(currentTag);
    currentTag = openTag;
}

void Parser::endTag()
{
    Tag *closeTag = parseCloseTag();
    if (currentTag->getType() != closeTag->getType()) throw;
    currentTag = currentTag->getParent();
}

void Parser::parseParameters()
{
    while (!isCloseTag())
    {
        if (current().type == Number)
        {
            currentTag->addValue(stod(current().text));
        }
        else if (current().type == String)
        {
            currentTag->addValues(findAttributeById(current().text).getValues());
        }
        else if (current().type == OpenBracket)
        {
            currentTag->addValues(parseExpression());
        }
        else 
        {
            throw;
        }
        next();
    }
}

Attribute Parser::findAttributeById(std::string id)
{
    Tag* tmp = currentTag;
    while (tmp && tmp->getAttribute().getId() != id)
    {
        tmp = tmp->getParent();
    }
    if (tmp == nullptr) throw;
    return tmp->getAttribute();
}

std::vector<double> Parser::parseExpression()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    if (current().text == "LET")
    {
        previous();
        return parseLetExpression();
    }
    previous();
    return parseNormalExpression();
}

std::vector<double> Parser::parseNormalExpression()
{
    startTag();
    parseParameters();
    std::vector<double> values = currentTag->eval();
    endTag();
    return values;
}

std::vector<double> Parser::parseLetExpression()
{
    startTag();
    currentTag->getAttribute().setValues(parseExpression());
    parseParameters();
    if (!isBodyTag()) throw;
    // parseBodyTag();
    std::vector<double> values = currentTag->eval();
    endTag();
    return values;
}

Tag* Parser::parseOpenTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::stot(current().text);
    next();
    if (current().type == Quote)
    {
        tag->getAttribute().setId(parseAttribute().getId());
        next();
    }
    if (current().type != CloseBracket) throw;
    next();
    return tag;
}

// Tag* Parser::parseBodyTag()
// {
//     if (current().type != OpenBracket) throw;
//     next();
//     if (current().text != "BODY") throw;
//     next();
//     if (current().type != Slash) throw;
//     next();
//     if (current().type != CloseBracket) throw;
//     next();
//     return new Tag();
// }

Tag* Parser::parseCloseTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::stot(current().text);
    if (current().type != CloseBracket) throw;
    next();
    return tag;
}

Attribute Parser::parseAttribute()
{
    if (current().type != Quote) throw;
    next();
    if (current().type != Number && current().type != String) throw;
    Attribute attribute;
    attribute.setId(current().text);
    next();
    if (current().type != Quote) throw;
    next();
    return attribute;
}