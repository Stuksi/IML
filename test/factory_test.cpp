#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/tag/factory.h"

inline void check(std::string type)
{
    iml::tag* tag = iml::factory::to_tag(type);
    CHECK(tag->as_string() == type);
    delete tag;
}

TEST_CASE("valid")
{
    check("MAP-INC");
    check("MAP-MLT");
    check("AGG-SUM");
    check("AGG-PRO");
    check("AGG-AVG");
    check("AGG-FST");
    check("AGG-LST");
    check("SRT-ORD");
    check("SRT-DST");
    check("SRT-REV");
    check("SRT-SLC");
    check("LET");
    check("BODY");
}

TEST_CASE("invalid")
{
    iml::tag* tag = nullptr;
    try
    {
        tag = iml::factory::to_tag("MAP");
        CHECK(false);
    }
    catch(const std::exception& e)
    {
        CHECK(true);
    }
    delete tag;
}