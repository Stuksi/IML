#include "../include/tag/tag.h"
#include <cassert>

namespace iml
{
    tag::tag() : type_(tag_null)
    {}

    tag::tag(tag_type type) : type_(type)
    {}

    tag::~tag()
    {}

    tag_type tag::type() const
    {
        return type_;
    }

    std::string tag::as_string() const
    {
        switch (type_)
        {
            case tag_null: return "NULL";
            case tag_map_inc: return "MAP-INC";
            case tag_map_mlt: return "MAP-MLT";
            case tag_agg_sum: return "AGG-SUM";
            case tag_agg_pro: return "AGG-PRO";
            case tag_agg_avg: return "AGG-AVG";
            case tag_agg_fst: return "AGG-FST";
            case tag_agg_lst: return "AGG-LST";
            case tag_srt_ord: return "SRT-ORD";
            case tag_srt_rev: return "SRT-REV";
            case tag_srt_dst: return "SRT-DST";
            case tag_srt_slc: return "SRT-SLC";
            case tag_let: return "SRT-LET";
            case tag_body: return "SRT-BODY";
            default: return "";
        }
    }

    attribute tag::attr() const
    {
        assert(false);
        return attribute();
    }
}