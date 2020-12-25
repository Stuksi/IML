#include "../include/interpreter/interpreter.h"
#include "../include/tag/factory.h"
#include "../include/tag/tag.h"
#include "../include/tag/tag_apply.h"
#include <cassert>

namespace iml
{
    // bool interpreter::is_body_expression()
    // {
    //     return hierarchy_.top()->type() == tag_let;
    // }

    void interpreter::evaluate_expression()
    {
        if (reader_.end())
        {
            return;
        }
        else if (reader_.is_value())
        {
            evaluate_value();
        }
        else
        {
            evaluate_tag_expression();
        } 
        evaluate_expression();
    }

    void interpreter::evaluate_value()
    {
        if (reader_.current().type == token_number)
        {
            if (values_.empty())
            {
                values_.push(std::list<double>());
            }
            values_.top().push_back(stod(reader_.current().text));
        }
        else 
        {
            assert(links_.find(reader_.current().text) != links_.end());
            for (double value : links_.at(reader_.current().text).top())
            {
                values_.top().push_back(value);
            }
        }
        reader_.next();
    }

    void interpreter::evaluate_tag_expression()
    {
        hierarchy_.push(reader_.read_open_tag());
        values_.push(std::list<double>());
        evaluate_expression();

        // if (is_body_expression())
        // {
        //     evaluate_body_expression();
        // }

        tag* close_tag = reader_.read_close_tag();
        assert(hierarchy_.top()->type() != close_tag->type());

        std::list<double> values = tag_apply::apply(values_.top(), hierarchy_.top());
        hierarchy_.pop();
        values_.pop();
        for (double value : values)
        {
            values_.top().push_back(value);
        }
    }

    // void interpreter::evaluate_body_expression()
    // {
    //     parser_->parse_body_tag();

    //     std::string name = hierarchy_.top()->attribute().text();
    //     links_[name].push(hierarchy_.top()->evaluate());
    //     hierarchy_.top()->clear();

    //     evaluate_expression();

    //     links_[name].pop();
    //     if (links_[name].empty())
    //     {
    //         links_.erase(name);
    //     }
    // }

    std::list<double> interpreter::evaluate(std::istream& in)
    {
        reader_ = reader(in);
        hierarchy_.push(new tag(tag_null));
        evaluate_expression();
        return values_.top();
    }
}
