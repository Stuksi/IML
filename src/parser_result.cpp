#include "../include/parser/parser_result.h"
#include <fstream>

namespace iml
{
    parser_result::parser_result(node* _root) : root(_root)
    {}
    
    parser_result::~parser_result()
    {
        delete root;
    }

    void parser_result::visualize(const char* tree_file_path)
    {
        std::ofstream out(tree_file_path);
        out << "digraph G {\n";
        root->visualize(out);
        out << "}";
        std::cout << "Visualization successful!" << std::endl;
    }

    void parser_result::evaluate(const char* result_file_path)
    {
        try
        {
            std::list<double> resulting_values = root->evaluate();
            std::ofstream out(result_file_path);
            std::cout << "Evaluation successful!\n";
            out << "Result: ";
            for (auto i = resulting_values.begin(); i != --resulting_values.end(); ++i)
            {
                out << *i << " ";
            }
            out << *(--resulting_values.end());
        }
        catch(const std::exception& e)
        {
            std::cout << "Evaluation error -> " << e.what() << std::endl;
        }        
    }
}