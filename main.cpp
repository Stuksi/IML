#include "include/parser/parser.h"
#include <sstream>
#include <fstream>

int main()
{
    std::stringstream ss;
    ss << "<MAP-INC \"1\"> 1 2 3 </MAP-INC>";
    iml::parser parser(ss);
    iml::parser_result result = parser.build_tree();

    std::ofstream out("tree.dot");
    out << "digraph G {\n";
    result.root->visualize(out);
    out << "}";

    return 0;
}