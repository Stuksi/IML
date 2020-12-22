#include "../include/iml core headers/iml_parser.h"
#include "../include/iml tag headers/iml_tag_factory.h"

iml_parser::iml_parser(std::istream& in) : tokens_(iml_tokenizer(in).tokenize()), tokens_iterator_(tokens_.begin())
{}

void iml_parser::next()
{
    ++tokens_iterator_;
}

void iml_parser::previous()
{
    --tokens_iterator_;
}

iml_token iml_parser::current() const
{
    return *tokens_iterator_;
}


void iml_parser::parse_token(iml_token_type type)
{
    if (current().type != type)
    {
        switch (type)
        {
            case iml_token_type::open_bracket: 
                throw std::logic_error("Expected open bracket character '<', given " + current().text + " !");
            
            case iml_token_type::close_bracket: 
                throw std::logic_error("Expected closed bracket character '>', given " + current().text + " !");
            
            case iml_token_type::slash: 
                throw std::logic_error("Expected slash character '/', given " + current().text + " !");
            
            case iml_token_type::quote: 
                throw std::logic_error("Expected quote character '\"', given " + current().text + " !"); 
            
            case iml_token_type::string: 
                throw std::logic_error("Expected string, given " + current().text + " !");
        }
    }
    next();
}

std::list<double> iml_parser::parse_value(const iml_name_links& links)
{
    std::list<double> values;
    if (current().type == iml_token_type::string) 
    {
        if (links.find(current().text) == links.end()) 
        {
            throw std::invalid_argument
                (
                    current().text 
                    + " is not defined!"
                );
        }
        values = links.at(current().text).top();
    }
    else
    {
        values = {stod(current().text)};
    }
    next();
    return values;
}

iml_tag_base* iml_parser::parse_open_tag()
{
    parse_token(iml_token_type::open_bracket);

    std::string tag_type = current().text;
    if(!iml_tag_factory::exists(tag_type))
    {
        throw std::invalid_argument
            (
                "Tag " 
                + tag_type
                + " does not exist!"
            );
    }
    parse_token(iml_token_type::string);

    iml_tag_base* tag = current().type == iml_token_type::quote ? iml_tag_factory::to_atag(tag_type, parse_attribute()) : iml_tag_factory::to_tag(tag_type);
    
    parse_token(iml_token_type::close_bracket);

    return tag;
}

iml_tag_base* iml_parser::parse_body_tag()
{
    parse_token(iml_token_type::open_bracket);

    if (current().text != "BODY") 
    {
        throw std::logic_error
            (
                "Expected string \"BODY\", given " 
                + current().text 
                + " ! Missing or invalid BODY tag syntax!"
            );
    }

    parse_token(iml_token_type::string);
    parse_token(iml_token_type::slash);
    parse_token(iml_token_type::close_bracket);

    return iml_tag_factory::to_tag("BODY");
}

iml_tag_base* iml_parser::parse_close_tag()
{
    parse_token(iml_token_type::open_bracket);
    parse_token(iml_token_type::slash);

    std::string tag_type = current().text;
    if(!iml_tag_factory::exists(tag_type))
    {
        throw std::invalid_argument
            (
                "Tag " 
                + tag_type 
                + " does not exist!"
            );
    }

    parse_token(iml_token_type::string);
    parse_token(iml_token_type::close_bracket);

    return iml_tag_factory::to_tag(tag_type);
}

iml_tag_attribute iml_parser::parse_attribute()
{
    parse_token(iml_token_type::quote);

    if (current().type != iml_token_type::number && current().type != iml_token_type::string) 
    {
        throw std::invalid_argument
            (
                "Attribute expects a value argument!"
            );
    }
    std::string attribute_text = current().text;
    next();

    parse_token(iml_token_type::quote);
    
    return iml_tag_attribute(attribute_text);
}

bool iml_parser::is_value() const
{
    return current().type == iml_token_type::number || current().type == iml_token_type::string;
}

bool iml_parser::is_end()
{
    if (current().type == iml_token_type::open_bracket)
    {
        next();
        if (current().type == iml_token_type::slash || current().text == "BODY")
        {
            previous();
            return true;
        }
        previous();
    }
    return current().text == "end_of_file()";
}

iml_token_position iml_parser::cursor_position() const
{
    return current().position;
}
