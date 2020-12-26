#include "../include/token/lexer.h"

namespace iml
{
    lexer::lexer(std::istream& _in) : in(_in)
    {}

    void lexer::cws()
    {
        while (in.peek() == ' ' || in.peek() == '\n')
        {
            in.get();
        }
    }

    token lexer::next_sign()
    {
        char c = in.get();
        switch (c)
        {
            case '<': return token {"<", token_open_bracket};
            case '>': return token {">", token_close_bracket};
            case '/': return token {"/", token_slash};
            case '\"': return token {"\"", token_quote};
            default: throw std::runtime_error("'" + std::string(1, c) + "' is not a recognisable character!");
        }
    }

    token lexer::next_string()
    {
        std::string text = "";
        while ((in.peek() >= 'A' && in.peek() <= 'Z') || in.peek() == '-')
        {
            text += in.get();
        } 
        return token {text, token_string};
    }

    token lexer::next_number()
    {
        double text;
        in >> text;
        return token {std::to_string(text), token_number};
    }

    token lexer::next()
    {
        cws();
        char c = in.peek();
        if (c >= 'A' && c <= 'Z')
        {
            return next_string();
        }
        else if ((c >= '0' && c <= '9') || c == '-')
        {
            return next_number();
        }
        return next_sign();
    }

    lexer_result lexer::tokenize()
    {
        std::list<token> tokens;
        token next_token;
        while (1)
        {
            try
            {
                next_token = next();
            }
            catch (const std::exception& e)
            {
                if (in.eof()) 
                {
                    break;
                }
                std::cerr << "Warning -> " << e.what() << std::endl;
                continue;
            }
            tokens.push_back(next_token);
        }
        tokens.push_back(token {"end_of_file", token_invalid});
        return lexer_result(tokens);
    }
}