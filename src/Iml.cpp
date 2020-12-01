#include "../include/Iml.h"
#include "../include/Parser.h"

void Iml::parse(std::istream& in, std::ostream& out)
{
    Parser parser(in);
    parser.build(out);
}