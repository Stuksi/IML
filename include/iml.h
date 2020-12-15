#ifndef __iml_h
#define __iml_h

#include <iostream>

class iml
{
private:
    iml_parser parser;
public:
    void parse_file(const char*, const char* = "iml_result.imlr");
    void parse_buffer(const char*, const char* = "iml_result.imlr");
    void parse_stream(std::istream&, const char* = "iml_result.imlr");
};

#endif