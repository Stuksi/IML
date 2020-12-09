#include "../include/iml.h"
#include "../include/iml_parser.h"
#include <fstream>

void iml::parse_file(const char* input_file_name, const char* output_file_name)
{
    std::ifstream in(input_file_name);
    std::ofstream out(output_file_name);
    iml_parser parser(in);
    parser.build(out);
}