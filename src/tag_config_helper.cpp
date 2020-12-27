#include "../include/tag/tag_config.h"
#include <set>
#include <stdexcept>
#include <iostream>

namespace iml
{
    template <tag_type T>
    std::list<double> tag_config::tag_config_helper<T>::map(std::list<double> values, std::function<void(double&)> op)
    {
        for (double& value : values)
        {
            op(value);
        }
        return values;
    }

    template <tag_type T>
    std::list<double> tag_config::tag_config_helper<T>::agg(std::list<double> values, std::function<double(double, double)> op, double def, std::function<double(double)> r)
    {
        if (values.empty())
        {
            return values;
        }
        double result = def;
        for (double& value : values)
        {
            result = op(result, value);
        }
        return {r(result)};
    }

    template <tag_type T>
    bool tag_config::tag_config_helper<T>::validate_attribute(tag* tag, std::function<bool(std::string)> pred, std::string def, std::string error_msg)
    {
        try
        {
            if (tag->get_attribute().empty()) throw std::runtime_error("Tag " + tag->as_string() + " expects an attribute!");
            std::string attr = tag->get_attribute().get_value();
            if (pred(attr)) throw std::runtime_error("Invalid attribute value '" + attr + "'! " + error_msg);
        }
        catch(const std::exception& e)
        {
            std::cerr << "Warning -> " << e.what() << std::endl;
            tag->set_attribute(attribute(def));
            return false;
        }
        return true;
    }

    template <tag_type T>
    std::list<double> tag_config::tag_config_helper<T>::apply(std::list<double> values, tag* tag)
    {
        return values;
    }

    template <tag_type T>
    bool tag_config::tag_config_helper<T>::validate(tag* tag)
    {
        return true;
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_map_inc>::apply(std::list<double> values, tag* tag)
    {
        double attr = tag->get_attribute().as_double();
        return map(values, [attr](double& value)
                            {
                                value += attr; 
                            });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_map_mlt>::apply(std::list<double> values, tag* tag)
    {
        double attr = tag->get_attribute().as_double();
        return map(values, [attr](double& value)
                            {
                                value *= attr; 
                            });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_agg_sum>::apply(std::list<double> values, tag* tag)
    {
        return agg(values, [](double result, double value)
                            {
                                return result + value;
                            }, 0, [](double result)
                                    {
                                        return result;
                                    });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_agg_pro>::apply(std::list<double> values, tag* tag)
    {
        return agg(values, [](double result, double value)
                            {
                                return result * value;
                            }, 1, [](double result)
                                    {
                                        return result;
                                    });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_agg_avg>::apply(std::list<double> values, tag* tag)
    {
        return agg(values, [](double result, double value)
                            {
                                return result + value;
                            }, 0, [values](double result)
                                    {
                                        return result/values.size();
                                    });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_agg_fst>::apply(std::list<double> values, tag* tag)
    {
        return agg(values, [](double result, double value)
                            {
                                return result;
                            }, 0, [values](double result)
                                    {
                                        return *values.begin();
                                    });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_agg_lst>::apply(std::list<double> values, tag* tag)
    {
        return agg(values, [](double result, double value)
                            {
                                return result;
                            }, 0, [values](double result)
                                    {
                                        return *(--values.end());
                                    });
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_srt_ord>::apply(std::list<double> values, tag* tag)
    {
        std::string attr = tag->get_attribute().get_value();
        if (attr == "ASC")
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
    std::list<double> tag_config::tag_config_helper<tag_srt_slc>::apply(std::list<double> values, tag* tag)
    {
        int attr = tag->get_attribute().as_int();
        std::list<double> result_values;
        std::list<double>::iterator values_it = values.begin();
        std::advance(values_it, attr);
        while (values_it != values.end())
        {
            result_values.push_back(*values_it);
            ++values_it;
        }
        return result_values;
    }

    template <>
    std::list<double> tag_config::tag_config_helper<tag_srt_dst>::apply(std::list<double> values, tag* tag)
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
    std::list<double> tag_config::tag_config_helper<tag_srt_rev>::apply(std::list<double> values, tag* tag)
    {
        values.reverse();
        return values;
    }

    template <>
    bool tag_config::tag_config_helper<tag_map_inc>::validate(tag* tag)
    {
        return validate_attribute(tag, [](std::string str)
        {
            return (str[0] != '-' && !isdigit(str[0]));
        }, "0", "Attribute exprects a real number value!");
    }

    template <>
    bool tag_config::tag_config_helper<tag_map_mlt>::validate(tag* tag)
    {
        return validate_attribute(tag, [](std::string str)
        {
            return (str[0] != '-' && !isdigit(str[0]));
        }, "1", "Attribute expects a real number value!");
    }

    template <>
    bool tag_config::tag_config_helper<tag_srt_ord>::validate(tag* tag)
    {
        return validate_attribute(tag, [](std::string str)
        {
            return str != "ASC" && str != "DSC";
        }, "ASC", "Attribute expects a 'ASC' or 'DSC' value!");
    }

    template <>
    bool tag_config::tag_config_helper<tag_srt_slc>::validate(tag* tag)
    {
        return validate_attribute(tag, [](std::string str)
        {
            for (char c : str)
            {
                if(!isdigit(c))
                {
                    return true;
                }
            }
            return false;
        }, "0", "Attribute expects a non-negative integer value!");
    }

    template <>
    bool tag_config::tag_config_helper<tag_let>::validate(tag* tag)
    {
        return validate_attribute(tag, [](std::string str)
        {
            for (char c : str)
            {
                if (!(c >= 'A' && c <= 'Z'))
                {
                    return true;  
                }   
            }
            return false;
        }, "X", "Attribute supports upper-case characters only!");
    }
}