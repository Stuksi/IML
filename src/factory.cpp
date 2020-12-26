#include "../include/tag/factory.h"
#include "../include/tag/tag.h"
#include "../include/tag/taga.h"
#include <stdexcept>

namespace iml
{
    tag* factory::to_tag(std::string type, attribute attr)
    {
        if (type == "MAP-INC") return new taga(tag_map_inc, attr);
        else if (type == "MAP-MLT") return new taga(tag_map_mlt, attr);
        else if (type == "AGG-SUM") return new tag(tag_agg_sum);
        else if (type == "AGG-PRO") return new tag(tag_agg_pro);
        else if (type == "AGG-AVG") return new tag(tag_agg_avg);
        else if (type == "AGG-FST") return new tag(tag_agg_fst);
        else if (type == "AGG-LST") return new tag(tag_agg_lst);
        else if (type == "SRT-ORD") return new taga(tag_srt_ord, attr);
        else if (type == "SRT-REV") return new tag(tag_srt_rev);
        else if (type == "SRT-DST") return new tag(tag_srt_dst);
        else if (type == "SRT-SLC") return new taga(tag_srt_slc, attr);
        else if (type == "LET") return new taga(tag_let, attr);
        else if (type == "BODY") return new tag(tag_body);
        throw std::runtime_error(type + " is not a recognisible tag type!");
    }
}