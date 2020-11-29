#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"
#include "Tag.h"

class Parser
{
private:
    std::vector<Token> tokenized;
    size_t it;

    void get();
    Token peek() const;

    std::vector<double> parse(Tag*);
public:
    Parser(std::istream&);
    void parse(std::ostream&);
};

#endif