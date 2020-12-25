#ifndef __reader_h
#define __reader_h

#include "../token/token.h"
#include "../tag/tag.h"
#include <list>
#include <iostream>

namespace iml
{
    class reader
    {
    private:
        std::list<token> tokens_;
        std::list<token>::iterator tokens_iterator_;
    public:      
        reader(std::istream&);

        token current() const;
        void next();
        void previous();
        bool end();
        bool is_value();

        tag* read_open_tag();
        tag* read_close_tag();
        attribute read_attribute();
    };
}


#endif