#include "../include/iml tag headers/iml_tag_type_converter.h"

static const std::string types_data[] = 
{
    "ROOT"
    , "MAP-INC"
    , "MAP-MLT"
    , "AGG-SUM"
    , "AGG-PRO"
    , "AGG-AVG"
    , "AGG-FST"
    , "AGG-LST"
    , "SRT-REV"
    , "SRT-ORD"
    , "SRT-SLC"
    , "SRT-DST"
    , "LET"
    , "BODY"
};
const std::string* iml_tag_type_converter::types = types_data;