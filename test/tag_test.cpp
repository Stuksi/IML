#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/tag/tag.h"

inline void check(iml::tag_type type, std::string str_type)
{
    iml::tag tag(type);
    CHECK(tag.as_string() == str_type);
}

TEST_CASE("default/get_type")
{
    iml::tag tag;
    CHECK(tag.get_type() == iml::tag_null); 
}

TEST_CASE("parameterized")
{
    iml::tag tag(iml::tag_body);
    CHECK(tag.get_type() == iml::tag_body); 
}

TEST_CASE("as_string")
{
    check(iml::tag_map_inc, "MAP-INC");
    check(iml::tag_map_mlt, "MAP-MLT");
    check(iml::tag_agg_sum, "AGG-SUM");
    check(iml::tag_agg_pro, "AGG-PRO");
    check(iml::tag_agg_avg, "AGG-AVG");
    check(iml::tag_agg_fst, "AGG-FST");
    check(iml::tag_agg_lst, "AGG-LST");
    check(iml::tag_srt_ord, "SRT-ORD");
    check(iml::tag_srt_dst, "SRT-DST");
    check(iml::tag_srt_slc, "SRT-SLC");
    check(iml::tag_srt_rev, "SRT-REV");
    check(iml::tag_let, "LET");
    check(iml::tag_body, "BODY");
    check(iml::tag_null, "NULL");
}

TEST_CASE("attribute")
{
    iml::tag tag(iml::tag_map_mlt);
    try
    {
        tag.get_attribute();
        CHECK(false);
    }
    catch(const std::exception& e)
    {
        CHECK(true);
    }
    try
    {
        tag.set_attribute(iml::attribute());
        CHECK(false);
    }
    catch(const std::exception& e)
    {
        CHECK(true);
    }
}