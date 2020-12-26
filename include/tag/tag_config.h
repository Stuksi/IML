#ifndef __tag_config_h
#define __tag_config_h

#include "tag.h"
#include <list>
#include <set>
#include <stdexcept>
#include <iostream>

namespace iml
{
    class tag_config
    {
    private:
        template <tag_type T>
        static std::list<double> apply(std::list<double>);
        template <tag_type T>
        static std::list<double> apply(std::list<double>, tag*);
        template <tag_type T>
        static bool validate(tag*);
    public:
        // Tag evaluation
        static std::list<double> apply(std::list<double>, tag*);
        // Tag validation
        static bool validate(tag*);
    };

    template <>
    inline std::list<double> tag_config::apply<tag_null>(std::list<double> values)
    {
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_map_inc>(std::list<double> values, tag* tag)
    {
        double attr = tag->get_attribute().as_double();
        for (double& value : values)
        {
            value += attr;
        }
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_map_mlt>(std::list<double> values, tag* tag)
    {
        double attr = tag->get_attribute().as_double();
        for (double& value : values)
        {
            value *= attr;
        }
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_agg_sum>(std::list<double> values)
    {
        if (values.empty())
        {
            return values;
        }
        double result = 0;
        for (double& value : values)
        {
            result += value;
        }
        return {result};
    }

    template <>
    inline std::list<double> tag_config::apply<tag_agg_pro>(std::list<double> values)
    {
        if (values.empty())
        {
            return values;
        }
        double result = 1;
        for (double& value : values)
        {
            result *= value;
        }
        return {result};
    }

    template <>
    inline std::list<double> tag_config::apply<tag_agg_avg>(std::list<double> values)
    {
        if (values.empty())
        {
            return values;
        }
        double result = 0;
        for (double& value : values)
        {
            result += value;
        }
        return {result/values.size()};
    }

    template <>
    inline std::list<double> tag_config::apply<tag_agg_fst>(std::list<double> values)
    {
        if (values.empty())
        {
            return values;
        }
        return {*values.begin()};
    }

    template <>
    inline std::list<double> tag_config::apply<tag_agg_lst>(std::list<double> values)
    {
        if (values.empty())
        {
            return values;
        }
        return {*(--values.end())};
    }

    template <>
    inline std::list<double> tag_config::apply<tag_srt_ord>(std::list<double> values, tag* tag)
    {
        if (tag->get_attribute().get_value() == "ASC")
        {
            values.sort([](double a, double b)->bool{return a > b;});
        }
        else
        {
            values.sort([](double a, double b)->bool{return a < b;});
        }
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_srt_slc>(std::list<double> values, tag* tag)
    {
        int attr = tag->get_attribute().as_int();
        if (tag->get_attribute().get_value() == "ASC")
        {
            values.sort([](double a, double b)->bool{return a > b;});
        }
        else
        {
            values.sort([](double a, double b)->bool{return a < b;});
        }
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_srt_dst>(std::list<double> values)
    {
        std::set<double> values_set;
        for (double value : values)
        {
            values_set.insert(value);
        }
        std::list<double> values_result;
        for (double value : values_set)
        {
            values_result.push_back(value);
        }
        return values_result;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_srt_rev>(std::list<double> values)
    {
        values.reverse();
        return values;
    }

    template <>
    inline std::list<double> tag_config::apply<tag_let>(std::list<double> values, tag* tag)
    {
        return values;
    }

    template <>
    inline bool tag_config::validate<tag_map_inc>(tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        try
        {
            if (attr[0] != '-' && !isdigit(attr[0]))
            {
                throw std::runtime_error("Invalid attribute value '" + attr + "'! Attribute expects a real number value!");
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->get_attribute().set_value(0);
            return false;
        }
        return true;
    }

    template <>
    inline bool tag_config::validate<tag_map_mlt>(tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        try
        {
            if (attr[0] != '-' && !isdigit(attr[0]))
            {
                throw std::runtime_error("Invalid attribute value '" + attr + "'! Attribute expects a real number value!");
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->get_attribute().set_value(0);
            return false;
        }
        return true;
    }

    template <>
    inline bool tag_config::validate<tag_srt_ord>(tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        try
        {
            if (attr != "ASC" && attr != "DSC")
            {
                throw std::runtime_error("Invalid attribute value '" + attr + "'! Attribute expects a 'ASC' or 'DSC' value!");
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->get_attribute().set_value("ASC");
            return false;
        }
        return true;
    }

    template <>
    inline bool tag_config::validate<tag_srt_slc>(tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        try
        {
            for (char c : attr)
            {
                if (!isdigit(attr[0]))
                {
                    throw std::runtime_error("Invalid attribute value '" + attr + "'! Attribute expects a non-negative integer value!");
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->get_attribute().set_value(0);
            return false;
        }
        return true;
    }

    template <>
    inline bool tag_config::validate<tag_let>(tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        try
        {
            for (char c : attr)
            {
                if (!(c >= 'A' && c <= 'Z'))
                {
                    throw std::runtime_error("Invalid attribute value '" + attr + "'! Attribute expects a non-negative integer value!");
                }
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->get_attribute().set_value("X");
            return false;
        }
        return true;
    }

    inline std::list<double> tag_config::apply(std::list<double> values, tag* tag)
    {
        switch (tag->get_type())
        {
            case tag_map_inc: return apply<tag_map_inc>(values, tag); 
            case tag_map_mlt: return apply<tag_map_mlt>(values, tag); 
            case tag_agg_sum: return apply<tag_agg_sum>(values); 
            case tag_agg_pro: return apply<tag_agg_pro>(values); 
            case tag_agg_avg: return apply<tag_agg_avg>(values); 
            case tag_agg_fst: return apply<tag_agg_fst>(values); 
            case tag_agg_lst: return apply<tag_agg_lst>(values); 
            case tag_srt_ord: return apply<tag_srt_ord>(values, tag); 
            case tag_srt_dst: return apply<tag_srt_dst>(values); 
            case tag_srt_slc: return apply<tag_srt_slc>(values, tag); 
            case tag_srt_rev: return apply<tag_srt_rev>(values); 
            case tag_let: return apply<tag_let>(values, tag); 
            case tag_null: return apply<tag_null>(values);
            default: return values;
        }
    }

    inline bool tag_config::validate(tag* tag)
    {
        switch (tag->get_type())
        {
            case tag_map_inc: return validate<tag_map_inc>(tag); 
            case tag_map_mlt: return validate<tag_map_mlt>(tag); 
            case tag_srt_ord: return validate<tag_srt_ord>(tag); 
            case tag_srt_slc: return validate<tag_srt_slc>(tag); 
            case tag_let: return validate<tag_let>(tag); 
            default: return true;
        }
    }
}

// #include "../../src/template/tag_config.cpp"

#endif