#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/tag/attribute.h"

TEST_CASE("default/get_value")
{
    iml::attribute attr;
    CHECK(attr.get_value() == "");
}

TEST_CASE("parameterized")
{
    iml::attribute attr("attribute");
    CHECK(attr.get_value() == "attribute");
}

TEST_CASE("set_value")
{
    iml::attribute attr("attribute");
    attr.set_value("X");
    CHECK(attr.get_value() == "X");
}

TEST_CASE("set_value type convertion")
{
    iml::attribute attr("attribute");
    attr.set_value(999);
    CHECK(attr.get_value() == "999.000000");
}

TEST_CASE("as_double")
{
    iml::attribute attr("123.123");
    CHECK(attr.as_double() == 123.123);
}

TEST_CASE("as_double invalid")
{
    iml::attribute attr("X");
    CHECK(attr.as_double() == 0);
}

TEST_CASE("as_int")
{
    iml::attribute attr("123");
    CHECK(attr.as_int() == 123);
}

TEST_CASE("as_int invalid")
{
    iml::attribute attr("X");
    CHECK(attr.as_int() == 0);
}

TEST_CASE("empty")
{
    iml::attribute attr;
    CHECK(attr.empty() == true);
}
