#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../lib/doctest.h"

#include "../include/tag/tag_config.h"
#include "../include/tag/factory.h"

std::list<double> test_list = {1, 3, 2, 5, 6, 4};

TEST_CASE("apply map-inc")
{
    iml::attribute attr("2.2");
    iml::tag* tag = iml::factory::to_tag("MAP-INC", attr);
    std::list<double>::iterator it = test_list.begin();
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == *it + attr.as_double());
        ++it;
    }
    delete tag;
}

TEST_CASE("validate map-inc")
{
    iml::attribute attr("X");
    iml::tag* tag = iml::factory::to_tag("MAP-INC", attr);
    iml::tag_config::validate(tag);
    CHECK(tag->get_attribute().get_value() == "0");
    delete tag;
}

TEST_CASE("apply map-mlt")
{
    iml::attribute attr("2.2");
    iml::tag* tag = iml::factory::to_tag("MAP-MLT", attr);
    std::list<double>::iterator it = test_list.begin();
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == *it * attr.as_double());
        ++it;
    }
    delete tag;
}

TEST_CASE("validate map-mlt")
{
    iml::attribute attr("X");
    iml::tag* tag = iml::factory::to_tag("MAP-MLT", attr);
    iml::tag_config::validate(tag);
    CHECK(tag->get_attribute().get_value() == "1");
    delete tag;
}

TEST_CASE("apply agg-sum")
{
    iml::tag* tag = iml::factory::to_tag("AGG-SUM");
    double sum = 0;
    for (double num : test_list)
    {
        sum += num;
    }
    CHECK(iml::tag_config::apply(test_list, tag).front() == sum);
    delete tag;
}

TEST_CASE("apply agg-pro")
{
    iml::tag* tag = iml::factory::to_tag("AGG-PRO");
    double pro = 1;
    for (double num : test_list)
    {
        pro *= num;
    }
    CHECK(iml::tag_config::apply(test_list, tag).front() == pro);
    delete tag;
}

TEST_CASE("apply agg-avg")
{
    iml::tag* tag = iml::factory::to_tag("AGG-AVG");
    double avg = 0;
    for (double num : test_list)
    {
        avg += num;
    }
    avg /= test_list.size();
    CHECK(iml::tag_config::apply(test_list, tag).front() == avg);
    delete tag;
}

TEST_CASE("apply agg-fst")
{
    iml::tag* tag = iml::factory::to_tag("AGG-FST");
    CHECK(iml::tag_config::apply(test_list, tag).front() == *test_list.begin());
    delete tag;
}

TEST_CASE("apply agg-lst")
{
    iml::tag* tag = iml::factory::to_tag("AGG-LST");
    CHECK(iml::tag_config::apply(test_list, tag).front() == *(--test_list.end()));
    delete tag;
}

TEST_CASE("apply srt-ord")
{
    iml::attribute attr("ASC");
    iml::tag* tag = iml::factory::to_tag("SRT-ORD", attr);
    double el = 1;
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == el);
        ++el;
    }

    attr.set_value("DSC");
    iml::tag* tag2 = iml::factory::to_tag("SRT-ORD", attr);
    el = 6;
    for (double num : iml::tag_config::apply(test_list, tag2))
    {
        CHECK(num == el);
        --el;
    }
    delete tag;
    delete tag2;
}

TEST_CASE("validate srt-ord")
{
    iml::attribute attr("X");
    iml::tag* tag = iml::factory::to_tag("SRT-ORD", attr);
    iml::tag_config::validate(tag);
    CHECK(tag->get_attribute().get_value() == "ASC");
}

TEST_CASE("apply srt-slc")
{
    iml::attribute attr("3");
    iml::tag* tag = iml::factory::to_tag("SRT-SLC", attr);
    std::list<double>::iterator it = test_list.begin();
    std::advance(it, 3);
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == *it);
        ++it;
    }
    delete tag;
}

TEST_CASE("validate srt-slc")
{
    iml::attribute attr("X");
    iml::tag* tag = iml::factory::to_tag("SRT-SLC", attr);
    iml::tag_config::validate(tag);
    CHECK(tag->get_attribute().get_value() == "0");
    delete tag;
}

TEST_CASE("apply srt-rev")
{
    iml::tag* tag = iml::factory::to_tag("SRT-REV");
    std::list<double>::iterator it = --test_list.end();
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == *it);
        --it;
    }
    delete tag;
}

TEST_CASE("apply srt-dst")
{
    iml::tag* tag = iml::factory::to_tag("SRT-DST");
    std::list<double> test = {1, 1, 1, 1, 2, 2, 1, 1, 4, 55, 4, 55, 3, 5};
    std::list<double> expected = {1, 2, 4, 55, 3, 5};
    std::list<double>::iterator it = expected.begin();
    for (double num : iml::tag_config::apply(test, tag))
    {
        CHECK(num == *it);
        ++it;
    }
    delete tag;
}

TEST_CASE("apply let")
{
    iml::tag* tag = iml::factory::to_tag("LET");
    std::list<double>::iterator it = test_list.begin();
    for (double num : iml::tag_config::apply(test_list, tag))
    {
        CHECK(num == *it);
        ++it;
    }
    delete tag;
}

TEST_CASE("validate let")
{
    iml::attribute attr("1");
    iml::tag* tag = iml::factory::to_tag("LET", attr);
    iml::tag_config::validate(tag);
    CHECK(tag->get_attribute().get_value() == "X");
    delete tag;
}

TEST_CASE("validate non-attribute tag")
{
    iml::attribute attr("1");
    iml::tag* tag = iml::factory::to_tag("AGG-PRO", attr);
    CHECK(iml::tag_config::validate(tag) == false);
    delete tag;
}