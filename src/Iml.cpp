#include "../include/Iml.h"
#include "../include/Parser.h"
#include <fstream>

void Iml::parse(const char* inputFileName, const char* outputFileName)
{
    std::ifstream in(inputFileName);
    std::ofstream out(outputFileName);
    Parser parser(in);
    parser.build(out);
}