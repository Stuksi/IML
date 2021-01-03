#include "../include/tag/tag.h"
#include <stdexcept>

namespace iml
{
    tag::tag() : type(tag_null)
    {}

    tag::tag(tag_type type) : type(type)
    {}

    tag_type tag::get_type() const
    {
        return type;
    }

    std::string tag::as_string() const
    {
        switch (type)
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
            case tag_let: return "LET";
            case tag_body: return "BODY";
            default: return "";
        }
    }

    attribute tag::get_attribute() const
    {
        throw std::runtime_error(as_string() + " type does not support attributes!");
    }

    void tag::set_attribute(attribute attr)
    {
        throw std::runtime_error(as_string() + " type does not support attributes!");
    }
}