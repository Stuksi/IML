#include "../include/IML Parsing/Parser.h"
#include "../include/Tag Factory/Factory.h"
#include "../include/IML Tags/Root.h"

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

Attribute* Parser::searchAttributeInHierarchy(std::string id)
{
    std::stack<Tag*> saveHierarchy;
    while (!hierarchy.empty() && hierarchy.top()->getAttribute()->getId() != id)
    {
        saveHierarchy.push(hierarchy.top());
        hierarchy.pop();
    }
    if (hierarchy.empty()) throw;
    Attribute *attribute = hierarchy.top()->getAttribute();
    while (!saveHierarchy.empty())
    {
        hierarchy.push(saveHierarchy.top());
        saveHierarchy.pop();
    }
    return attribute;
}

void Parser::parseValue()
{
    if (current().type == Minus)
    {
        next();
        if (current().type != Number) throw;
        hierarchy.top()->addValue(-stod(current().text));
    }
    else if(current().type == Number)
    {
        hierarchy.top()->addValue(stod(current().text));
    }
    else 
    {   
        hierarchy.top()->addValue(searchAttributeInHierarchy(current().text)->getValues());
    }
    next();
}

void Parser::parseOpenTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::stringToTag(current().text);
    hierarchy.push(tag);
    next();
    if (current().type == Quote)
    {
        parseAttribute();
    }
    else
    {
        try
        {
            tag->getAttribute();
            throw std::logic_error("");  
        }
        catch(const std::logic_error& e)
        {
            throw;
        }
        // catch(const std::invalid_argument& e)
        // {}
    }
    if (current().type != CloseBracket) throw;
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
    if (hierarchy.top()->getType() != Factory::stringToTagType(current().text)) throw;
    next();
    if (current().type != CloseBracket) throw;
    std::vector<double> result = hierarchy.top()->eval();
    hierarchy.pop();
    hierarchy.top()->addValue(result);
    next();
}

void Parser::parseAttribute()
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
    hierarchy.top()->setAttribute(attribute);
    next();
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
    hierarchy.top()->moveValuesToAttribute();
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
    hierarchy.push(new Root());
    try
    {
        parseExpression();
        if (hierarchy.size() != 1) throw;
        std::vector<double> parsingResult = hierarchy.top()->getValues();
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