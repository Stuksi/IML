#ifndef __IML_PARSER_H
#define __IML_PARSER_H

#include "iml_tokenizer.h"
#include "iml_node.h"

class iml_parser
{
private:
    iml_node_struct* document_root;

    list<iml_token> tokens;
    size_t it;
public:
    iml_parser(iml_tokenizer_result&);
    
    void next();
    iml_token current() const;
    void create_document_tree();
};

#endif