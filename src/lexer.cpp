#include "../include/token/lexer.h"

namespace iml
{
    lexer::lexer(std::istream& in) : in_(in)
    {}

    token lexer::next()
    {
        while (in_.peek() == ' ' || in_.peek() == '\n')
        {
            in_.get();
        }
        char c = in_.peek();
        if (c >= 'A' && c <= 'Z')
        {
            std::string text = "";
            while ((in_.peek() >= 'A' && in_.peek() <= 'Z') || in_.peek() == '-')
            {
                text += in_.get();
            } 
            return token {text, token_string};
        }
        else if ((c >= '0' && c <= '9') || c == '-')
        {
            double text;
            in_ >> text;
            return token {std::to_string(text), token_number};
        }
        in_.get();
        switch (c)
        {
            case '<': return token {"<", token_open_bracket};
            case '>': return token {">", token_close_bracket};
            case '/': return token {"/", token_slash};
            case '\"': return token {"\"", token_quote};
            default: return token {"?", token_invalid};
        }
    }

    lexer_result lexer::tokenize()
    {
        std::list<token> tokens;
        token next_token;
        while (1)
        {
            next_token = next();
            if (in_.eof() && next_token.type == token_invalid)
            {
                break;
            }
            tokens.push_back(next_token);
        }
        tokens.push_back(token {"end_of_file", token_invalid});
        return lexer_result {tokens};
    }
}