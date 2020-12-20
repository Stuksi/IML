#define DOCTEST_CONFIG_IMPLEMENT
#include "../lib/doctest.h"
#include "../include/iml_tag_base.h"
#include "../include/iml_tag.h"

TEST_CASE("type")
{
    iml_tag_base* tag = new iml_tag<iml_tag_type::iml_root>();
    CHECK(tag->type() == iml_tag_type::iml_root);
}

TEST_CASE("add(values)/values")
{
    iml_tag_base* tag = new iml_tag<iml_tag_type::iml_root>();
    std::list<double> exp = {};
    tag->add({});
    CHECK(tag->values() == exp);
    tag->add({1, 2, 3, 4});
    exp = {1, 2, 3, 4};
    CHECK(tag->values() == exp);
    tag->add({5, 6, 7, 8});
    CHECK(tag->values() != exp);
    exp = {1, 2, 3, 4, 5, 6, 7, 8};
    CHECK(tag->values() == exp);
}

TEST_CASE("add(value)/values")
{
    iml_tag_base* tag = new iml_tag<iml_tag_type::iml_root>();
    std::list<double> exp = {};
    tag->add(1);
    CHECK(tag->values() != exp);
    tag->add(2);
    exp = {1, 2};
    CHECK(tag->values() == exp);
}

TEST_CASE("clear")
{
    iml_tag_base* tag = new iml_tag<iml_tag_type::iml_root>();
    std::list<double> exp = {};
    tag->add({1, 2, 3});
    CHECK(tag->values() != exp);
    tag->clear();
    CHECK(tag->values() == exp);
}

TEST_CASE("attribute")
{
    iml_tag_base* tag = new iml_tag<iml_tag_type::iml_root>();
    try
    {
        tag->attribute();
        CHECK(false);
    }
    catch(const std::exception& e)
    {
        CHECK(true);
    }
}

int main()
{
    doctest::Context().run();
    return 0;
}