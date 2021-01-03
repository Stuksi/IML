#include "../include/interpreter/interpreter.h"

int main()
{
    iml::interpreter i;
    i.interpret_file("iml_file_example.iml");
    return 0;
}