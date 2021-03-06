#include "../include/interpreter/interpreter.h"
#include "../include/tag/factory.h"
#include "../include/tag/tag_config.h"
#include <fstream>
#include <sstream>

namespace iml
{
    bool interpreter::is_body_expr()
    {
        return tags.top()->get_type() == tag_let;
    }

    void interpreter::expr()
    {
        if (r.is_end())
        {
            return;
        }
        else if (r.is_value())
        {
            value_expr();
        }
        else
        {
            tag_expr();
        } 
        expr();
    }

    void interpreter::value_expr()
    {
        if (r.current().type == token_number)
        {
            values.top().push_back(stod(r.current().text));
        }
        else 
        {
            if(links.find(r.current().text) == links.end()) throw std::runtime_error(r.current().text + " is not defined!");
            
            for (double value : links.at(r.current().text).top())
            {
                values.top().push_back(value);
            }
        }
        r.next();
    }

    void interpreter::tag_expr()
    {
        tag* open_tag = r.read_open_tag();
        tags.push(open_tag);
        values.push(std::list<double>());
        expr();

        if (is_body_expr())
        {
            body_expr();
        }

        tag* close_tag = r.read_close_tag();
        if (tags.top()->get_type() != close_tag->get_type()) throw std::runtime_error("Wrong closing tag for - " + tags.top()->as_string() + ". Given - " + close_tag->as_string() + "!");

        std::list<double> list_values = tag_config::apply(values.top(), tags.top());
        
        tags.pop();
        values.pop();
        delete open_tag;
        delete close_tag;

        for (double value : list_values)
        {
            values.top().push_back(value);
        }
    }

    void interpreter::body_expr()
    {
        tag* body_tag = r.read_body_tag();

        std::string name = tags.top()->get_attribute().get_value();
        links[name].push(values.top());
        values.top().clear();

        expr();

        links[name].pop();
        if (links[name].empty())
        {
            links.erase(name);
        }

        delete body_tag;
    }

    std::list<double> interpreter::evaluate()
    {
        tag* root_tag = new tag(tag_null);
        
        tags.push(root_tag);
        values.push(std::list<double>());
        
        expr();

        delete root_tag;
        
        return values.top();
    }
    
    void interpreter::interpret_file(const char* in_file_path, const char* out_file_path)
    {
        std::ifstream in(in_file_path);
        if (!in.is_open())
        {
            std::cout << "Error -> Non existing input file!" << std::endl;
            return;
        }
        
        r = reader(in);
        try
        {
            std::list<double> resulting_values = evaluate();
            std::ofstream out(out_file_path);
            std::cout << "Evaluation successfull!\n";
            out << "Result: ";
            if (resulting_values.size() > 0)
            {
                for (auto i = resulting_values.begin(); i != --resulting_values.end(); ++i)
                {
                    out << *i << " ";
                }
                out << *(--resulting_values.end()); 
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Error -> " << e.what() << std::endl;
            std::cout << "Evaluation failed!" << std::endl;
        }
    }
}


