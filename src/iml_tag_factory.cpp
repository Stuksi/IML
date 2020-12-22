#include "../include/iml tag headers/iml_tag_factory.h"
#include "../include/iml tag headers/iml_tag.h"
#include "../include/iml tag headers/iml_atag.h"
#include <stdexcept>

bool iml_tag_factory::exists(std::string type)
{
    return type == "MAP-INC"
        || type == "MAP-MLT"
        || type == "AGG-SUM"
        || type == "AGG-PRO"
        || type == "AGG-AVG"
        || type == "AGG-FST"
        || type == "AGG-LST"
        || type == "SRT-REV"
        || type == "SRT-ORD"
        || type == "SRT-SLC"
        || type == "SRT-DST"
        || type == "BODY"
        || type == "LET";
}

iml_tag_base* iml_tag_factory::to_tag(std::string type)
{
    iml_tag_base* tag;
    if (type == "AGG-SUM")
    {
        tag = new iml_tag<iml_tag_type::agg_sum>();
    }
    else if (type == "AGG-PRO")
    {
        tag = new iml_tag<iml_tag_type::agg_pro>();
    }
    else if (type == "AGG-AVG")
    {
        tag = new iml_tag<iml_tag_type::agg_avg>();
    }
    else if (type == "AGG-FST")
    {
        tag = new iml_tag<iml_tag_type::agg_fst>();
    }
    else if (type == "AGG-LST")
    {
        tag = new iml_tag<iml_tag_type::agg_lst>();
    }
    else if (type == "SRT-REV")
    {
        tag = new iml_tag<iml_tag_type::srt_rev>();
    }
    else if (type == "SRT-DST")
    {
        tag = new iml_tag<iml_tag_type::srt_dst>();
    }
    else if (type == "BODY")
    {
        tag = new iml_tag<iml_tag_type::body>();
    }
    else
    {
        throw std::invalid_argument
            (
                "Tag, "
                + type
                + " must be provided with an attribute!"
            );
    }
    return tag;
}

iml_tag_base* iml_tag_factory::to_atag(std::string type, iml_tag_attribute attribute)
{
    iml_tag_base* tag;
    if (type == "MAP-INC")
    {
        tag = new iml_atag<iml_tag_type::map_inc>(attribute);
    }
    else if (type == "MAP-MLT")
    {
        tag = new iml_atag<iml_tag_type::map_mlt>(attribute);
    }
    else if (type == "SRT-ORD")
    {
        tag = new iml_atag<iml_tag_type::srt_ord>(attribute);
    }
    else if (type == "SRT-SLC")
    {
        tag = new iml_atag<iml_tag_type::srt_slc>(attribute);
    }
    else if (type == "LET")
    {
        tag = new iml_atag<iml_tag_type::let>(attribute);
    }
    else
    {
        throw std::invalid_argument
            (
                "Tag, "
                + type
                + " can not be provided with an attribute!"
            );
    }
    return tag;
}
