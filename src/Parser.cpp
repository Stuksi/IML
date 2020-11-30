#include "../include/Parser.h"
#include "../include/Factory.h"

Parser::Parser(std::istream& in) : tokenized(Tokenizer(in).tokenize()), it(0), root(new Tag()), currentTag(root)
{}

void Parser::next()
{
    it++;
}

void Parser::previous()
{
    it--;
}

Attribute Parser::findAttribute(std::string id)
{
    Tag *tmp = currentTag;
    while (tmp && tmp->getAttribute().getId() != id)
    {
        tmp = tmp->getParent();
    }
    if (tmp == nullptr) throw;
    return tmp->getAttribute();
}

Token Parser::current()
{
    return tokenized[it];
}

Tag* Parser::parseOpenTag()
{
    if (current().type != Open) throw;
    next();
    if (current().type != Text) throw;
    Tag* tag = Factory::sToTag(current().text);
    next();
    if (current().type == Quote)
    {
        tag->setAttribute(parseAttribute());
    }
    next();
    if (current().type != Close) throw;
    return tag;
}

Tag* Parser::parseCloseTag()
{
    if (current().type != Open) throw;
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != Text) throw;
    Tag* tag = Factory::sToTag(current().text);
    next();
    if (current().type != Close) throw;
    return tag;
}

Tag* Parser::parseBodyTag()
{
    if (current().type != Open) throw;
    next();
    if (current().type != Text) throw;
    if (current().text != "BODY") throw;
    Tag* tag = new Tag();
    next();
    if (current().type != Slash) throw;
    next();
    if (current().type != Close) throw;
    return tag;
}

Attribute Parser::parseAttribute()
{
    if (current().type != Quote) throw;
    Attribute attribute;
    next();
    if (current().type != Text && current().type != Number) throw;
    attribute.setId(current().text); 
    if (current().type != Quote) throw;
    return attribute;
}

std::vector<double> Parser::parseExpression()
{
    if (current().type != Open) throw;
    next();
    if (current().type != Text) throw;
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
    Tag* parent = currentTag;
    currentTag = parseOpenTag();
    currentTag->setParent(parent);
    next();
    while (1)
    {
        if (current().type == Number)
        {
            currentTag->addValue(stod(current().text));
        }
        else if (current().type == Text)
        {
            Attribute attribute = findAttribute(current().text);
            currentTag->addValues(attribute.getValues());
        }
        else if (current().type == Open)
        {
            next();
            if (current().type == Slash)
            {
                
            }
            currentTag->addValues(parseExpression());
        }
    }
    
}

/*
    EXPR := {NORMALEXPR | LETEXPR}
    NORMALEXPR := OPENTAG , {NUM | TXT | OPENTAG} , CLOSETAG
    LETEXPR := OPENTAG , {NUM | TXT | OPENTAG} , BODYTAG , {NUM | TXT} , CLOSETAG
    ATTRIBUTE := " , TXT | NUM , "
    OPENTAG := < , TXT , [ ATTRIBUTE ] , >
    BODYTAG := < , BODY , / , >
    CLOSETAG := < , / , TXT , >
    TXT := {CHAR}
    NUM := 0 , NUMNOZERO | [ - ] , NUMNOZERO
    CHAR := A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q | R | S | T | U | V | W | X | Y | Z
    NUMNOZERO := 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 , {NUM}

    [ * ] -> Either * is or isn't included.
    *+  -> Include the * 1 or more times.
    { * } -> Include the * 0 or more times.
    | -> or
*/