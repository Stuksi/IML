#include "../include/Parser.h"
#include "../include/Factory.h"

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

bool Parser::more()
{
    return it < tokenized.size();
}

Token Parser::current()
{
    return tokenized[it];
}

bool Parser::isValue()
{
    return current().type == Minus || current().type == Number || current().type == String;
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

void Parser::startExpression()
{
    Tag *start = parseOpenTag();
    start->setParent(currentTag);
    currentTag = start;
}

void Parser::endExpression()
{
    Tag *end = parseCloseTag();
    if (currentTag->getType() != end->getType()) throw;
    delete end;
    Tag *save = currentTag;
    currentTag = currentTag->getParent();
    delete save;
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
    if (isValue())
    {
        parseValueExpression();
        if (more() && !isBodyTag() && !isCloseTag()) return parseExpression();
        return currentTag->eval();
    }
    else if (isLetTag())
    {
        return parseLetExpression();
    }
    return parseNormalExpression();
}

std::vector<double> Parser::parseNormalExpression()
{
    startExpression();
    while (!isCloseTag()) parseExpression();
    std::vector<double> values = currentTag->eval();
    endExpression();
    return values;
}

std::vector<double> Parser::parseLetExpression()
{
    startExpression();
    Tag *saveCurrentTag = currentTag;
    currentTag = new Tag();
    currentTag->getAttribute().setValues(parseExpression());
    saveCurrentTag->getAttribute().setValues(currentTag->eval());
    delete currentTag;
    currentTag = saveCurrentTag;
    if (!isBodyTag()) throw;
    parseBodyTag();
    while (!isCloseTag()) parseExpression();
    std::vector<double> values = currentTag->eval();
    endExpression();
    return values;
}

Tag* Parser::parseOpenTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::sToTag(current().text);
    next();
    if (current().type == Quote)
    {
        if (!tag->hasNumberAttribute() && !tag->hasStringAttribute()) throw;
        Attribute attribute = parseAttribute();
        if (tag->hasNumberAttribute() && attribute.getType() != NumberAttribute) throw;
        if (tag->hasStringAttribute() && attribute.getType() != StringAttribute) throw;
        tag->setAttribute(attribute);
    }
    else if (tag->hasNumberAttribute() || tag->hasStringAttribute())
    {
        throw;
    }
    if (current().type != CloseBracket) throw;
    next();
    return tag;
}

Tag* Parser::parseBodyTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().text != "BODY") throw;
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != CloseBracket) throw;
    next();
    return new Tag();
}

Tag* Parser::parseCloseTag()
{
    if (current().type != OpenBracket) throw;
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != String) throw;
    Tag *tag = Factory::sToTag(current().text);
    next();
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
    if (current().type == Number) attribute.setType(NumberAttribute);
    if (current().type == String) attribute.setType(StringAttribute);
    next();
    if (current().type != Quote) throw;
    next();
    return attribute;
}

void Parser::parseValueExpression()
{
    if (current().type == Minus)
    {
        next();
        if (current().type != Number) throw;
        currentTag->addValue(-stod(current().text));
    }
    else if (current().type == Number)
    {
        currentTag->addValue(stod(current().text));
    }
    else if (current().type == String)
    {
        currentTag->addValue(findAttributeById(current().text).getValues());
    }
    next();
}

void Parser::build(std::ostream& out)
{
    try
    {
        std::vector<double> parsingResult = parseExpression();
        if (currentTag->getType() != Root) throw;
        delete currentTag;
        size_t parsingResultSize = parsingResult.size() - 1;
        for (size_t i = 0; i < parsingResultSize; i++)
        {
            out << parsingResult[i] << " ";
        }
        out << parsingResult[parsingResultSize];
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        out << e.what();
    }
}