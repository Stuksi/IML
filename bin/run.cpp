#include "../include/Iml.h"
#include "../include/Tokenizer.h"
#include <fstream>

int main()
{
    std::ifstream imlFile("input.iml");
    std::ofstream txtFile("output.txt");

    Iml::parse(imlFile, txtFile);

    return 0;
}