#include "../include/IML Parsing/Iml.h"
#include "../include/IML Parsing/Parser.h"
#include <fstream>

void Iml::parse(const char* inputFileName, const char* outputFileName)
{
    std::ifstream in(inputFileName);
    std::ofstream out(outputFileName);
    Parser parser(in);
    parser.build(out);
}