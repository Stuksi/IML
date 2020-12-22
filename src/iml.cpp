#include "../include/iml core headers/iml.h"
#include <fstream>
#include <sstream>

void iml::write_out(std::list<double> list, std::ostream& out)
{
    out << "Evaluation successfull!\n";
    out << "Resulting array: [";
    for (auto i = list.begin(); i != --list.end(); ++i)
    {
        out << *i << ", ";
    }
    out << *(--list.end()) << "];";
}

void iml::interpret(std::istream& in, const char* output_file_path)
{
    try 
    {
        std::list<double> list = interpreter_->evaluate(in);
        std::ofstream out(output_file_path);
        write_out(list, out);
        out.close();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void iml::interpret_file(const char* input_file_path, const char* output_file_path)
{
    std::ifstream in(input_file_path);
    interpret(in, output_file_path);
    in.close();
}

void iml::interpret_buffer(const char* input_buffer, const char* output_file_path)
{
    std::stringstream in;
    in << input_buffer;
    interpret(in, output_file_path);
}

void iml::interpret_stream(std::istream& input_stream, const char* output_file_path)
{
    interpret(input_stream, output_file_path);
}
