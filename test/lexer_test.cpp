#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/token/lexer.h"
#include <sstream>

inline iml::token_type type(std::string text)
{
    if ((text[0] >= '0' && text[0] <= '9') || text[0] == '-')
    {
        return iml::token_number;
    }
    else if(text[0] >= 'A' && text[0] <= 'Z')
    {
        return iml::token_string;
    }
    switch (text[0])
    {
    case '<':
        return iml::token_open_bracket;
    case '>':
        return iml::token_close_bracket;
    case '"':
        return iml::token_quote;
    case '/':
        return iml::token_slash;
    default:
        return iml::token_invalid;
    }
}

inline void check(const char* text)
{
    std::stringstream ss1, ss2;
    ss1 << text;
    ss2 << text;

    std::string current;
    iml::lexer lex(ss2);
    std::list<iml::token> exp;
    
    while (ss1 >> current)
    {
        exp.push_back(iml::token {current, type(current)});
    }
    
    exp.push_back(iml::token {"end_of_file", iml::token_invalid}); 
    std::list<iml::token>::iterator exp_it = exp.begin();

    for (iml::token token : lex.tokenize().tokens)
    {
        CHECK(token.type == (*exp_it).type);
        CHECK(token.text == (*exp_it).text);
        exp_it++;
    }
}

TEST_CASE("default")
{
    check("");
}

TEST_CASE("signs")
{
    check("< > / \"");
}

TEST_CASE("strings")
{
    check("IML IS A NICE LANGUAGE");
}

TEST_CASE("positive numbers")
{
    check("1.000000 12.000000 123.000000 1234.000000 1.000000 1.010000 1.012000 1.012300 0.000000 0.010000 0.012000 0.012300 123.000000 123.010000 123.012000 123.012300");
}

TEST_CASE("negative numbers")
{
    check("-1.000000 -12.000000 -123.000000 -1234.000000 -1.000000 -1.010000 -1.012000 -1.012300 -0.000000 -0.010000 -0.012000 -0.012300 -123.000000 -123.010000 -123.012000 -123.012300");
}

TEST_CASE("invalid strings")
{
    std::stringstream ss;
    ss << "iml is a nice language";
    iml::lexer lex(ss);
    for (iml::token token : lex.tokenize().tokens)
    {
        CHECK(token.text == "end_of_file");
        CHECK(token.type == iml::token_invalid);
    }
}

TEST_CASE("IML")
{
    check("< LET \" X \" > 1.000000 2.900000 123.123400 < BODY / > < MAP-INC \" -14.000000 \" > 200.000000 100.000000 300.000000 < / MAP-INC > 173.000000 288.000000 < / LET >");
}