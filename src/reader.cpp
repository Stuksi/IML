#include "../include/reader/reader.h"
#include "../include/token/lexer.h"
#include "../include/tag/factory.h"
#include <cassert>

namespace iml
{
    reader::reader(std::istream& in) : tokens_(lexer(in).tokenize().tokens), tokens_iterator_(tokens_.begin())
    {}

    token reader::current() const
    {
        return *tokens_iterator_;
    }

    void reader::next()
    {
        ++tokens_iterator_;
    }

    void reader::previous()
    {
        --tokens_iterator_;
    }

    bool reader::end()
    {
        if (current().type == token_open_bracket)
        {
            next();
            if (current().type == token_slash)
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
        assert(current().type == token_open_bracket);
        next();
        
        assert(current().type == token_string);
        std::string tag_type = current().text;
        next();

        attribute tag_attribute;
        if (current().type == token_quote)
        {
            tag_attribute = read_attribute();
        }

        assert(current().type == token_close_bracket);
        next();

        return factory::to_tag(tag_type, tag_attribute);
    }

    tag* reader::read_close_tag()
    {
        assert(current().type == token_open_bracket);
        next();
        assert(current().type == token_slash);
        next();
        
        assert(current().type == token_string);
        std::string close_tag = current().text;
        next();
        
        assert(current().type == token_close_bracket);
        next();

        return factory::to_tag(close_tag, attribute());
    }

    attribute reader::read_attribute()
    {
        assert(current().type == token_quote);
        next();
        
        assert(current().type == token_string || current().type == token_number);
        std::string attr = current().text;
        next();

        assert(current().type == token_quote);
        next();
        return attribute(attr);
    }
}