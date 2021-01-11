#include "../include/reader/reader.h"
#include "../include/token/lexer.h"
#include "../include/tag/factory.h"
#include "../include/tag/tag_config.h"

namespace iml
{
    reader::reader(std::istream& in) : tokens(lexer(in).tokenize())
    {}

    token reader::current() const
    {
        return *tokens.tokens_it;
    }

    void reader::next()
    {
        ++tokens.tokens_it;
    }

    void reader::previous()
    {
        --tokens.tokens_it;
    }

    void reader::read_token(token_type type)
    {
        if (current().type != type)
        {
            switch (type)
            {
                case token_open_bracket: throw std::runtime_error("Expected '<', given - '" + current().text + "' !");
                case token_close_bracket: throw std::runtime_error("Expected '>', given - '" + current().text + "' !");
                case token_slash: throw std::runtime_error("Expected '/', given - '" + current().text + "' !");
                case token_quote: throw std::runtime_error("Expected '\"', given - '" + current().text + "' !");
                case token_string: throw std::runtime_error("Expected 'string', given - '" + current().text + "' !");
            }
        }
        next();
    }

    bool reader::is_end()
    {
        if (current().type == token_open_bracket)
        {
            next();
            if (current().type == token_slash || current().text == "BODY")
            {
                previous();
                return true;
            }
            previous();
        }
        return current().text == "end_of_file";
    }

    bool reader::is_value()
    {
        return current().type == token_number || current().type == token_string;
    }

    tag* reader::read_open_tag()
    {
        read_token(token_open_bracket);
        std::string tag_type = current().text;
        read_token(token_string);
        attribute tag_attribute;
        if (current().type == token_quote)
        {
            tag_attribute = read_attribute();
        }
        read_token(token_close_bracket);

        tag* tag = factory::to_tag(tag_type, tag_attribute);
        tag_config::validate(tag);
        return tag;
    }

    tag* reader::read_close_tag()
    {
        read_token(token_open_bracket);
        read_token(token_slash);
        std::string close_tag = current().text;
        read_token(token_string);
        read_token(token_close_bracket);

        return factory::to_tag(close_tag);
    }

    tag* reader::read_body_tag()
    {
        read_token(token_open_bracket);
        if (current().text != "BODY") throw std::runtime_error("Expected 'BODY', given - '" + current().text + "' !");
        read_token(token_string);
        read_token(token_slash);
        read_token(token_close_bracket);

        return new tag(tag_body);
    }

    attribute reader::read_attribute()
    {
        read_token(token_quote);
        std::string attr = "";
        if (is_value())
        {
            attr = current().text;
            next();
        }
        read_token(token_quote);

        return attribute(attr);
    }
}