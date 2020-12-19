#include "../include/iml.h"
#include <fstream>
#include <sstream>

void iml::interpret_file(const char* input_file_path, const char* output_file_path)
{
    std::ifstream in(input_file_path);
    std::ofstream out(output_file_path);
    interpreter.build(in, out);
    in.close();
    out.close();
}

void iml::interpret_buffer(const char* input_buffer, const char* output_file_path)
{
    std::stringstream ss;
    ss << input_buffer;
    std::ofstream out(output_file_path);
    interpreter.build(ss, out);
    out.close();
}

void iml::interpret_stream(std::istream& input_stream, const char* output_file_path)
{
    std::ofstream out(output_file_path);
    interpreter.build(input_stream, out);
    out.close();
}
