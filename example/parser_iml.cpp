#include "../include/parser/parser.h"

int main()
{
    iml::parser parser;
    iml::parser_result result = parser.build_tree("iml_file_example.iml");
    result.evaluate();
    result.visualize();
    result.save();
}
