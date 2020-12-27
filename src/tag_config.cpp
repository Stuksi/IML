#include "../include/tag/tag_config.h"
#include <iostream>

namespace iml
{
    std::list<double> tag_config::apply(std::list<double> values, tag* tag)
    {
        switch (tag->get_type())
        {
            case tag_map_inc: return tag_config_helper<tag_map_inc>::apply(values, tag); 
            case tag_map_mlt: return tag_config_helper<tag_map_mlt>::apply(values, tag); 
            case tag_agg_sum: return tag_config_helper<tag_agg_sum>::apply(values); 
            case tag_agg_pro: return tag_config_helper<tag_agg_pro>::apply(values); 
            case tag_agg_avg: return tag_config_helper<tag_agg_avg>::apply(values); 
            case tag_agg_fst: return tag_config_helper<tag_agg_fst>::apply(values); 
            case tag_agg_lst: return tag_config_helper<tag_agg_lst>::apply(values); 
            case tag_srt_ord: return tag_config_helper<tag_srt_ord>::apply(values, tag); 
            case tag_srt_dst: return tag_config_helper<tag_srt_dst>::apply(values); 
            case tag_srt_slc: return tag_config_helper<tag_srt_slc>::apply(values, tag); 
            case tag_srt_rev: return tag_config_helper<tag_srt_rev>::apply(values); 
            default: return values;
        }
    }

    bool tag_config::validate(tag* tag)
    {
        switch (tag->get_type())
        {
            case tag_map_inc: return tag_config_helper<tag_map_inc>::validate(tag); 
            case tag_map_mlt: return tag_config_helper<tag_map_mlt>::validate(tag); 
            case tag_srt_ord: return tag_config_helper<tag_srt_ord>::validate(tag); 
            case tag_srt_slc: return tag_config_helper<tag_srt_slc>::validate(tag); 
            case tag_let: return tag_config_helper<tag_let>::validate(tag); 
        }
        if (!tag->get_attribute().empty())
        {
            std::cerr << "Warning -> " << "Tag " + tag->as_string() + " does not support attributes!";
            return false;
        }
        return true;
    }
}