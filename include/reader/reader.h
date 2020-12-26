#ifndef __reader_h
#define __reader_h

#include "../token/lexer_result.h"
#include "../tag/tag.h"
#include <list>
#include <iostream>

namespace iml
{
    class reader
    {
    private:
        lexer_result tokens;

        void read_token(token_type);
    public: 
        reader() = default;
        reader(std::istream&);

        // Accessors and mutators
        token current() const;
        void next();
        void previous();
        
        // Predicates
        bool is_end();
        bool is_value();

        // Reading the input stream
        tag* read_open_tag();
        tag* read_close_tag();
        tag* read_body_tag();
        attribute read_attribute();
    };
}


#endif