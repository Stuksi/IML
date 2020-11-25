#include "../include/iml_parser.h"

iml_parser::iml_parser(iml_tokenizer_result& tokenizer_result) : tokens(tokenizer_result.tokens), it(0)
{}

void iml_parser::next()
{
    it++;
}

iml_token iml_parser::current() const
{
    return tokens[it];
}

void create_document_tree()
{
    
}