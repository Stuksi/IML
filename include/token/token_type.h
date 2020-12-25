#ifndef __token_type_h
#define __token_type_h

namespace iml
{
    enum token_type
    {
        token_invalid,
        token_number,
        token_string,
        token_open_bracket,
        token_close_bracket,
        token_slash,
        token_quote
    };
}

#endif