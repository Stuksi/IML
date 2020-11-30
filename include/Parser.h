#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"
#include "Tag.h"
#include "Attribute.h"

class Parser
{
private:
    std::vector<Token> tokenized;
    size_t it;
    Tag *root, *currentTag;

    void next();
    void previous();
    Attribute findAttribute(std::string);
    Token current();

    Tag* parseOpenTag();
    Tag* parseCloseTag();
    Tag* parseBodyTag();
    Attribute parseAttribute();
    std::vector<double> parseExpression();
    std::vector<double> parseNormalExpression();
    std::vector<double> parseLetExpression();

public:
    Parser(std::istream&);
};

#endif