#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/reader/reader.h"
#include <sstream>

TEST_CASE("default")
{
    std::stringstream ss;
    try
    {
        iml::reader r;
        CHECK(true);
    }
    catch(const std::exception& e)
    {
        CHECK(false);
    }  
}

TEST_CASE("parameterized")
{
    std::stringstream ss;
    try
    {
        iml::reader r(ss);
        CHECK(true);
    }
    catch(const std::exception& e)
    {
        CHECK(false);
    }
}

TEST_CASE("current")
{
    std::stringstream ss;
    ss << "<AGG-AVG> 1 2 3 4 5 </AGG-AVG>";
    iml::reader r(ss);
    CHECK(r.current().text == "<");
    CHECK(r.current().type == iml::token_open_bracket);
}


TEST_CASE("next")
{
    std::stringstream ss;
    ss << "<AGG-AVG> 1 2 3 </AGG-AVG>";
    iml::reader r(ss);
    CHECK(r.current().text == "<");
    CHECK(r.current().type == iml::token_open_bracket);
    r.next();
    CHECK(r.current().text == "AGG-AVG");
    CHECK(r.current().type == iml::token_string);
    r.next();
    CHECK(r.current().text == ">");
    CHECK(r.current().type == iml::token_close_bracket);
    r.next();
    CHECK(r.current().text == "1.000000");
    CHECK(r.current().type == iml::token_number);
    r.next();
    CHECK(r.current().text == "2.000000");
    CHECK(r.current().type == iml::token_number);
    r.next();
    CHECK(r.current().text == "3.000000");
    CHECK(r.current().type == iml::token_number);
    r.next();
    CHECK(r.current().text == "<");
    CHECK(r.current().type == iml::token_open_bracket);
    r.next();
    CHECK(r.current().text == "/");
    CHECK(r.current().type == iml::token_slash);
    r.next();
    CHECK(r.current().text == "AGG-AVG");
    CHECK(r.current().type == iml::token_string);
    r.next();
    CHECK(r.current().text == ">");
    CHECK(r.current().type == iml::token_close_bracket);
    r.next();
    CHECK(r.current().text == "end_of_file");
    CHECK(r.current().type == iml::token_invalid);
}

TEST_CASE("previous")
{
    std::stringstream ss;
    ss << "<AGG-AVG> 1 2 3 </AGG-AVG>";
    iml::reader r(ss);
    CHECK(r.current().text == "<");
    CHECK(r.current().type == iml::token_open_bracket);
    r.previous();
    r.previous();
    CHECK(r.current().text == "end_of_file");
    CHECK(r.current().type == iml::token_invalid);
    r.previous();
    CHECK(r.current().text == ">");
    CHECK(r.current().type == iml::token_close_bracket);
    r.previous();
    CHECK(r.current().text == "AGG-AVG");
    CHECK(r.current().type == iml::token_string);
    r.previous();
    CHECK(r.current().text == "/");
    CHECK(r.current().type == iml::token_slash);
    r.previous();
    CHECK(r.current().text == "<");
    CHECK(r.current().type == iml::token_open_bracket);
    r.previous();
    CHECK(r.current().text == "3.000000");
    CHECK(r.current().type == iml::token_number);
    r.previous();
    CHECK(r.current().text == "2.000000");
    CHECK(r.current().type == iml::token_number);
    r.previous();
    CHECK(r.current().text == "1.000000");
    CHECK(r.current().type == iml::token_number);
    r.previous();
    CHECK(r.current().text == ">");
    CHECK(r.current().type == iml::token_close_bracket);
    r.previous();
    CHECK(r.current().text == "AGG-AVG");
    CHECK(r.current().type == iml::token_string);    
}

TEST_CASE("is_end")
{
    std::stringstream ss;
    ss << "<AGG-AVG> 1 2 3 </AGG-AVG>";
    iml::reader r(ss);
    CHECK(r.is_end() == false);
    r.next();
    r.next();
    r.next();
    r.next();
    r.next();
    r.next();
    CHECK(r.is_end() == true);
    r.next();
    r.next();
    CHECK(r.is_end() == false);
    r.next();
    r.next();
    CHECK(r.is_end() == true);
}

TEST_CASE("is_value")
{
    std::stringstream ss;
    ss << "<AGG-AVG> 1 X 2 Y 3 </AGG-AVG>";
    iml::reader r(ss);
    CHECK(r.is_value() == false);
    r.next();
    r.next();
    r.next();
    CHECK(r.is_value() == true);
    r.next();
    CHECK(r.is_value() == true);
    r.next();
    CHECK(r.is_value() == true);
    r.next();
    CHECK(r.is_value() == true);
    r.next();
    CHECK(r.is_value() == true);
    r.next();
    CHECK(r.is_value() == false);
}

TEST_CASE("read_open_tag")
{
    std::stringstream ss;
    ss << "<AGG-AVG>";
    iml::reader r(ss);
    iml::tag* tag = r.read_open_tag();
    CHECK(tag->get_type() == iml::tag_agg_avg);
    CHECK(tag->as_string() == "AGG-AVG");
}

TEST_CASE("invalid read_open_tag")
{
    std::stringstream ss;
    ss << "<AGG-AVG";
    iml::reader r(ss);
    try {
        iml::tag* tag = r.read_open_tag();
        CHECK(false);
    } 
    catch (const std::exception& e)
    {
        CHECK(true);
    }
}

TEST_CASE("read_close_tag")
{
    std::stringstream ss;
    ss << "</AGG-AVG>";
    iml::reader r(ss);
    iml::tag* tag = r.read_close_tag();
    CHECK(tag->get_type() == iml::tag_agg_avg);
    CHECK(tag->as_string() == "AGG-AVG");
}

TEST_CASE("invalid read_close_tag")
{
    std::stringstream ss;
    ss << "<AGG-AVG>";
    iml::reader r(ss);
    try {
        iml::tag* tag = r.read_close_tag();
        CHECK(false);
    } 
    catch (const std::exception& e)
    {
        CHECK(true);
    }
}

TEST_CASE("read_body_tag")
{
    std::stringstream ss;
    ss << "<BODY/>";
    iml::reader r(ss);
    iml::tag* tag = r.read_body_tag();
    CHECK(tag->get_type() == iml::tag_body);
    CHECK(tag->as_string() == "BODY");
}

TEST_CASE("invalid read_body_tag")
{
    std::stringstream ss;
    ss << "</BODY>";
    iml::reader r(ss);
    try {
        iml::tag* tag = r.read_body_tag();
        CHECK(false);
    } 
    catch (const std::exception& e)
    {
        CHECK(true);
    }
}

TEST_CASE("read_attribute")
{
    std::stringstream ss;
    ss << "\"X\"";
    iml::reader r(ss);
    iml::attribute attr = r.read_attribute();
    CHECK(attr.get_value() == "X");
    CHECK(attr.as_double() == 0);
    CHECK(attr.empty() == false);
}

TEST_CASE("invalid read_attribute")
{
    std::stringstream ss;
    ss << "<\"X>";
    iml::reader r(ss);
    try {
        iml::attribute attr = r.read_attribute();
        CHECK(false);
    } 
    catch (const std::exception& e)
    {
        CHECK(true);
    }
}