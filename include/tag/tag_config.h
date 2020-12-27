#ifndef __tag_config_h
#define __tag_config_h

#include "tag.h"
#include <list>
#include <functional>

namespace iml
{
    class tag_config
    {
    private:
        template <tag_type T>
        class tag_config_helper
        {
        private:
            static std::list<double> map(std::list<double>, std::function<void(double&)>);
            static std::list<double> agg(std::list<double>, std::function<double(double, double)>, double, std::function<double(double)>);
            static bool validate_attribute(tag*, std::function<bool(std::string)>, std::string, std::string);
        public:
            static std::list<double> apply(std::list<double>, tag* = new tag());
            static bool validate(tag*);
        };
    public:
        // Tag evaluation
        static std::list<double> apply(std::list<double>, tag* = new tag());
        // Tag validation
        static bool validate(tag*);
    };
}

#endif