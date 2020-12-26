#include "../include/token/lexer_result.h"

namespace iml
{
    lexer_result::lexer_result(std::list<token> _tokens) : tokens(_tokens), tokens_it(tokens.begin())
    {}
}