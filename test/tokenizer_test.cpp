#define DOCTEST_CONFIG_IMPLEMENT
#include "../lib/doctest.h"
#include "../include/iml_tokenizer.h"

#include <sstream>

inline iml_token_type type(std::string text)
{
    if ((text[0] >= '0' && text[0] <= '9') || text[0] == '-')
    {
        return iml_token_type::number;
    }
    else if(text[0] >= 'A' && text[0] <= 'Z')
    {
        return iml_token_type::string;
    }
    switch (text[0])
    {
    case '<':
        return iml_token_type::open_bracket;
    case '>':
        return iml_token_type::close_bracket;
    case '"':
        return iml_token_type::quote;
    case '/':
        return iml_token_type::slash;
    default:
        return iml_token_type::invalid;
    }
}

inline void invalid(const char* text)
{
    std::stringstream ss;
    ss << text;
    iml_tokenizer tokenizer(ss);
    try
    {
        tokenizer.tokenize();
        CHECK(false);
    }
    catch(...)
    {
        CHECK(true);
    }
}

inline void correct(const char* text)
{
    std::stringstream ss1, ss2;
    ss1 << text;
    ss2 << text;

    std::string current;
    iml_tokenizer tokenizer(ss2);
    std::list<iml_token> exp;
    size_t row = 1, col = 1;
    
    while (ss1 >> current)
    {
        exp.push_back(iml_token {type(current), current, iml_token_position {row, col}});
        col += current.length() + 1;
        if (ss1.peek() == '\n')
        {
            row++;
            col = 1;
        }
    }
    
    exp.push_back(iml_token {iml_token_type::invalid, "end_of_file()", iml_token_position {row, col}}); 
    std::list<iml_token>::iterator exp_it = exp.begin();

    for (iml_token token : tokenizer.tokenize())
    {
        CHECK(token.type == (*exp_it).type);
        CHECK(token.text == (*exp_it).text);
        CHECK(token.position.col == (*exp_it).position.col);
        CHECK(token.position.row == (*exp_it).position.row);
        exp_it++;
    }
}

TEST_CASE("default constructor")
{
    std::stringstream ss;
    ss << "";
    iml_tokenizer tokenizer(ss);
    CHECK(tokenizer.tokenize().size() == 1);
}

TEST_CASE("tokenize signs")
{
    correct("< > / \"");
}

TEST_CASE("tokenize invalid")
{
    invalid("?");
}

TEST_CASE("tokenize strings")
{
    correct("IML IS A NICE LANGUAGE");
}

TEST_CASE("tokenize invalid strings")
{
    invalid("iml"); 
}

TEST_CASE("tokenize numbers")
{
    correct("1 12 123 1234 1.0 1.01 1.012 1.0123 0.0 0.01 0.012 0.0123 123.0 123.01 123.012 123.0123\n-1 -12 -123 -1234 -1.0 -1.01 -1.012 -1.0123 -0.0 -0.01 -0.012 -0.0123 -123.0 -123.01 -123.012 -123.0123");
}

TEST_CASE("tokenize invelid numbers")
{
    invalid("01");
    invalid(".1");
    invalid("-.1");
    invalid("0.");
    invalid("01.2");
}

int main()
{
    doctest::Context().run();
    return 0;
}