#include "include/interpreter/interpreter.h"
#include <sstream>
#include <fstream>

int main()
{
    iml::interpreter interpreter;
    interpreter.interpret_file("iml_in.iml");

    return 0;
}