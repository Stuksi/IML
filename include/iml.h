#ifndef __iml_h
#define __iml_h

#include "iml_interpreter.h"

class iml
{
private:
    iml_interpreter interpreter;
public:
    void interpret_file(const char*, const char* = "iml_result.imlr");
    void interpret_buffer(const char*, const char* = "iml_result.imlr");
    void interpret_stream(std::istream&, const char* = "iml_result.imlr");
};

#endif