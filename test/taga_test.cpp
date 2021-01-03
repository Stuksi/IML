#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/tag/taga.h"

// inline void check(iml::tag_type type, std::string str_type)
// {
//     iml::taga tag(type, iml::attribute());
//     CHECK(tag.as_string() == str_type);
// }

TEST_CASE("parameterized/get_type")
{
    iml::taga tag(iml::tag_map_inc, iml::attribute("1"));
    CHECK(tag.get_type() == iml::tag_map_inc); 
}

// TEST_CASE("as_string")
// {
//     check(iml::tag_map_inc, "MAP-INC");
//     check(iml::tag_map_mlt, "MAP-MLT");
//     check(iml::tag_agg_sum, "AGG-SUM");
//     check(iml::tag_agg_pro, "AGG-PRO");
//     check(iml::tag_agg_avg, "AGG-AVG");
//     check(iml::tag_agg_fst, "AGG-FST");
//     check(iml::tag_agg_lst, "AGG-LST");
//     check(iml::tag_srt_ord, "SRT-ORD");
//     check(iml::tag_srt_dst, "SRT-DST");
//     check(iml::tag_srt_slc, "SRT-SLC");
//     check(iml::tag_srt_rev, "SRT-REV");
//     check(iml::tag_let, "LET");
//     check(iml::tag_body, "BODY");
//     check(iml::tag_null, "NULL");
// }

TEST_CASE("attribute")
{
    iml::taga tag(iml::tag_map_mlt, iml::attribute("1"));
    CHECK(tag.get_attribute().get_value() == "1");
    tag.set_attribute(iml::attribute("2"));
    CHECK(tag.get_attribute().get_value() == "2");
}