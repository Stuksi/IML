#include "../include/iml.h"
#include "../include/iml_parser.h"
#include <fstream>
#include <sstream>

void iml::parse_file(const char* input_file_path, const char* output_file_path)
{
    std::ifstream in(input_file_path);
    std::ofstream out(output_file_path);
    parser.build(in, out);
    in.close();
    out.close();
}

void iml::parse_buffer(const char* input_buffer, const char* output_file_path)
{
    std::stringstream ss;
    ss << input_buffer;
    std::ofstream out(output_file_path);
    parser.build(ss, out);
    out.close();
}

void iml::parse_stream(std::istream& input_stream, const char* output_file_path)
{
    std::ofstream out(output_file_path);
    iml_parser parser;
    parser.build(input_stream, out);
    out.close();
}
