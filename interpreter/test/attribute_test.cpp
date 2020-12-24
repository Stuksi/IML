#define DOCTEST_CONFIG_IMPLEMENT
#include "../lib/doctest.h"
#include "../include/iml_attribute.h"

TEST_CASE("default constructor")
{
    iml_attribute attr;
    CHECK(attr.text() == "");
}

TEST_CASE("parameterized constructor")
{
    iml_attribute attr("1");
    CHECK(attr.text() == "1");
}

TEST_CASE("empty")
{
    iml_attribute attr("1");
    CHECK(attr.empty() != true);
    iml_attribute attr2("");
    CHECK(attr2.empty() == true);
}

int main()
{
    doctest::Context().run();
    return 0;
}