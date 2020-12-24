#ifndef __iml_parser_h
#define __iml_parser_h

#include "../iml token headers/iml_tokenizer.h"
#include "../iml tag headers/iml_tag_base.h"
#include <unordered_map>
#include <stack>

typedef iml_tag_base* tag;
typedef std::unordered_map<std::string, std::stack<std::list<double>>> iml_name_links;

class iml_parser
{
private:
    std::list<iml_token> tokens_;
    std::list<iml_token>::iterator tokens_iterator_;
    void next();
    void previous();
    iml_token current() const;
    void parse_token(iml_token_type);
public:
    iml_parser(std::istream&);
    std::list<double> parse_value(const iml_name_links&);
    tag parse_open_tag();
    tag parse_body_tag();
    tag parse_close_tag();
    iml_tag_attribute parse_attribute();
    bool is_value() const;
    bool is_end();
    iml_token_position cursor_position() const;
};

#endif