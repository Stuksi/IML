#include "../include/Parser.h"
#include "../include/Factory.h"

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

bool Parser::more()
{
    return it < tokenized.size();
}

bool Parser::isValue()
{
    return current().type == Minus || current().type == Number || current().type == String;
}

bool Parser::isLetTag()
{
    if (current().type == OpenBracket)
    {
        next();
        if (current().text == "LET")
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

Token Parser::current()
{
    return tokenized[it];
}

void Parser::moveValuesToAttribute()
{
    hierachy.top()->getAttribute().setValues(hierachy.top()->eval());
    hierachy.top()->setValues(std::vector<double>());
}

Attribute Parser::searchAttributeInHierachy(std::string id)
{
    std::stack<Tag*> saveHierachy;
    while (!hierachy.empty() && hierachy.top()->getAttribute().getId() != id)
    {
        saveHierachy.push(hierachy.top());
        hierachy.pop();
    }
    if (hierachy.empty()) throw;
    Attribute attribute = hierachy.top()->getAttribute();
    while (!saveHierachy.empty())
    {
        hierachy.push(saveHierachy.top());
        saveHierachy.pop();
    }
    return attribute;
}

void Parser::parseValue()
{
    if (current().type == Minus)
    {
        next();
        if (current().type != Number) throw;
        hierachy.top()->addValue(-stod(current().text));
    }
    else if(current().type == Number)
    {
        hierachy.top()->addValue(stod(current().text));
    }
    else 
    {   
        hierachy.top()->addValue(searchAttributeInHierachy(current().text).getValues());
    }
    next();
}

void Parser::parseOpenTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::stringToTag(current().text);
    next();
    if (current().type == Quote)
    {
        if (!tag->hasAttribute()) throw;
        tag->setAttribute(parseAttribute());
    }
    else if (tag->hasAttribute())
    {
        throw;
    }
    if (current().type != CloseBracket) throw;
    hierachy.push(tag);
    next();
}

void Parser::parseBodyTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().text != "BODY") throw;
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != CloseBracket) throw;
    next();
}

void Parser::parseCloseTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != String) throw;
    if (hierachy.top()->getType() != Factory::stringToTagType(current().text)) throw;
    next();
    if (current().type != CloseBracket) throw;
    std::vector<double> result = hierachy.top()->eval();
    hierachy.pop();
    hierachy.top()->addValue(result);
    next();
}

Attribute Parser::parseAttribute()
{
    if (current().type != Quote) throw;
    next();
    if (!isValue()) throw;
    Attribute attribute;
    if (current().type == Minus)
    {
        next();
        if (current().type != Number) throw;
        attribute = Attribute("-" + current().text);
    }
    else
    {
        attribute = Attribute(current().text);
    }
    next();
    if (current().type != Quote) throw;
    next();
    return attribute;
}

void Parser::parseExpression()
{
    if (!more() || isBodyTag() || isCloseTag())
    {
        return;
    } 
    else if (isValue())
    {
        parseValue();
    }
    else if (isLetTag())
    {
        parseLetExpression();
    }
    else 
    {
        parseNormalExpression();
    }
    parseExpression();
}

void Parser::parseLetExpression()
{
    parseOpenTag();
    parseExpression();
    parseBodyTag();
    moveValuesToAttribute();
    parseExpression();
    parseCloseTag();
}

void Parser::parseNormalExpression()
{
    parseOpenTag();
    parseExpression();
    parseCloseTag();
}

void Parser::build(std::ostream& out)
{
    hierachy.push(new Tag());
    try
    {
        parseExpression();
        if (hierachy.size() != 1) throw;
        std::vector<double> parsingResult = hierachy.top()->getValues();
        size_t parsingSize = parsingResult.size() - 1;
        for (size_t i = 0; i < parsingSize; i++)
        {
            out << parsingResult[i] << " ";
        }
        out << parsingResult[parsingSize];
    }
    catch(const std::exception& e)
    {
        out << e.what();
    }
}