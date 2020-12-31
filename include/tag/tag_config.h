#ifndef __tag_config_h
#define __tag_config_h

#include "tag.h"
#include <list>
#include <functional>

namespace iml
{
    /// Tag configuration.
    ///
    /// Used to validate and apply the different mechanisms of the diffrent tag types.
    class tag_config
    {
    private:
        /// Helper class to simplify the methods using tag type templates.
        template <tag_type T>
        class tag_config_helper
        {
        private:
            //! Basic map function (helper function).
            static std::list<double> map(std::list<double>, std::function<void(double&)>);
            //! Basic reduce funtion (helper function).
            static std::list<double> agg(std::list<double>, std::function<double(double, double)>, double, std::function<double(double)>);
            //! Validates the attribute of the tag (if an error occurs a message is displayed and the default value of the attribute is set). 
            static bool validate_attribute(tag*, std::function<bool(std::string)>, std::string, std::string);
        public:
            //! Applies the tag mechanism to a list based on the tag type.
            static std::list<double> apply(std::list<double>, tag* = new tag());
            //! Validates the tag information based on the tag type.
            static bool validate(tag*);
        };
    public:
        //! Applies the tag mechanism to a list.
        static std::list<double> apply(std::list<double>, tag* = new tag());
        //! Validates the tag information (if an error occurs a message is displayed and the default values of the tag are set).
        static bool validate(tag*);
    };
}

#endif