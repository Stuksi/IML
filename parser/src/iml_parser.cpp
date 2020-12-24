#include "iml_parser.h"
#include <cassert>

namespace iml
{
    // Attribute
    attribute::attribute() : value_("")
    {}

    attribute::attribute(string value) : value_(value)
    {}

    bool attribute::empty() const
    {
        return value_ == "";
    }

    string attribute::value() const
    {
        return value_;
    }

    double attribute::as_number() const
    {
        double value;
        try
        {
            value = stod(value_);
        }
        catch(...)
        {
            value = 0;
        }
        return value;
    }

    // Node
    node::node() : type_(node_null)
    {}

    node::node(node_type type) : type_(type)
    {}

    node::~node()
    {}

    node_type node::type() const
    {
        return type_;
    }

    // node_iterator node::begin()
    // {
        
    // }

    // node_iterator node::end()
    // {

    // }

    // Node const
    node_const::node_const() : node(node_element), value_(0)
    {}

    node_const::node_const(string value) : node(node_element)
    {
        try
        {
            value_ = stod(value);
        }
        catch(...)
        {
            value_ = 0;
        }
    }
    
    node_const::~node_const()
    {}
    
    void node_const::visualize(ostream& out) const
    {
        out << (long)this << "[label=\"" << value_ << "\"];\n";
    }
    
    list<double> node_const::evaluate() const
    {
        return {value_};
    }

    // Node tag
    node_tag::node_tag() : tag_(nullptr), children_(list<node*>())
    {}

    node_tag::node_tag(tag_base* tag, list<node*> children) : tag_(tag), children_(children)
    {}

    node_tag::~node_tag()
    {
        for (node*& child : children_)
        {
            delete child;
        }
    }

    void node_tag::visualize(ostream& out) const
    {
        out << (long)this << "[label=\"" << "Tag: " << tag_->as_string() << "\"];\n";
        for (node* child : children_)
        {
            out << (long)this << "->" << (long)child << ";\n";
            child->visualize(out);
        }
    }

    list<double> node_tag::evaluate() const
    {
        list<double> values;
        for (node* child : children_)
        {
            for (double value : child->evaluate())
            {
                values.push_back(value);
            }
        }
        return tag_->apply(values);
    }

    // Tag base class
    tag_base::tag_base() : type_(tag_null)
    {}

    tag_base::tag_base(tag_type type) : type_(type)
    {}

    tag_base::~tag_base()
    {}

    tag_type tag_base::type() const
    {
        return type_;
    }

    string tag_base::as_string() const
    {
        switch (type_)
        {
            case tag_null: return "NULL";
            case tag_map_inc: return "MAP-INC";
            case tag_map_mlt: return "MAP-MLT";
            case tag_agg_sum: return "AGG-SUM";
            case tag_agg_pro: return "AGG-PRO";
            case tag_agg_avg: return "AGG-AVG";
            case tag_agg_fst: return "AGG-FST";
            case tag_agg_lst: return "AGG-LST";
            case tag_srt_ord: return "SRT-ORD";
            case tag_srt_rev: return "SRT-REV";
            case tag_srt_dst: return "SRT-DST";
            case tag_srt_slc: return "SRT-SLC";
            case tag_let: return "SRT-LET";
            case tag_body: return "SRT-BODY";
            default: return "";
        }
    }

    attribute tag_base::attr() const
    {
        assert(false);
        return attribute();
    }

    taga_base::taga_base() : attribute_(attribute())
    {}

    taga_base::taga_base(tag_type type, attribute attribute) : tag_base(type), attribute_(attribute)
    {}

    taga_base::~taga_base()
    {}

    attribute taga_base::attr() const
    {
        return attribute_;
    }

    // Tag factory
    tag_base* tag_factory::to_tag(string type, attribute attr)
    {
        if (type == "MAP-INC")
        {
            return new taga<tag_map_inc>(attr);
        }
        else if (type == "MAP-MLT")
        {
            return new taga<tag_map_mlt>(attr);
        }
        else if (type == "AGG-SUM")
        {
            return new tag<tag_agg_sum>();
        }
        else if (type == "AGG-PRO")
        {
            return new tag<tag_agg_pro>();
        }
        else if (type == "AGG-AVG")
        {
            return new tag<tag_agg_avg>();
        }
        else if (type == "AGG-FST")
        {
            return new tag<tag_agg_fst>();
        }
        else if (type == "AGG-LST")
        {
            return new tag<tag_agg_lst>();
        }
        else if (type == "SRT-ORD")
        {
            return new taga<tag_srt_ord>(attr);
        }
        else if (type == "SRT-REV")
        {
            return new tag<tag_srt_rev>();
        }
        else if (type == "SRT-DST")
        {
            return new tag<tag_srt_dst>();
        }
        else if (type == "SRT-SLC")
        {
            return new taga<tag_srt_slc>(attr);
        }
        else if (type == "LET")
        {
            return new taga<tag_let>(attr);
        }
        else if (type == "BODY")
        {
            return new tag<tag_body>();
        }
        return new tag<tag_null>();
    }

    // Lexer
    lexer::lexer(istream& in) : in_(in)
    {}

    token lexer::next()
    {
        while (in_.peek() == ' ' || in_.peek() == '\n')
        {
            in_.get();
        }
        char c = in_.peek();
        if (c >= 'A' && c <= 'Z')
        {
            string text = "";
            while ((in_.peek() >= 'A' && in_.peek() <= 'Z') || in_.peek() == '-')
            {
                text += in_.get();
            } 
            return token {text, token_string};
        }
        else if ((c >= '0' && c <= '9') || c == '-')
        {
            double text;
            in_ >> text;
            return token {to_string(text), token_number};
        }
        in_.get();
        switch (c)
        {
            case '<': return token {"<", token_open_bracket};
            case '>': return token {">", token_close_bracket};
            case '/': return token {"/", token_slash};
            case '\"': return token {"\"", token_quote};
            default: return token {"?", token_invalid};
        }
    }

    lexer_result lexer::tokenize()
    {
        list<token> tokens;
        while (in_)
        {
            token next_token = next();
            if (!in_ && next_token.text == "?")
            {
                break;
            }
            tokens.push_back(next_token);
        }
        return lexer_result {tokens};
    }

    parser::parser(istream& in) : tokens_(lexer(in).tokenize().tokens), tokens_iterator_(tokens_.begin())
    {}

    token parser::current() const
    {
        return *tokens_iterator_;
    }

    void parser::next()
    {
        ++tokens_iterator_;
    }

    void parser::previous()
    {
        --tokens_iterator_;
    }

    bool parser::end()
    {
        if (current().type == token_open_bracket)
        {
            next();
            if (current().type == token_slash)
            {
                previous();
                return true;
            }
            previous();
        }
        return false;
    }

    tag_base* parser::parse_open_tag()
    {
        assert(current().type == token_open_bracket);
        next();
        
        assert(current().type == token_string);
        string tag_type = current().text;
        next();

        attribute tag_attribute;
        if (current().type == token_quote)
        {
            tag_attribute = parse_attribute();
        }

        assert(current().type == token_close_bracket);
        next();

        return tag_factory::to_tag(tag_type, tag_attribute);
    }

    tag_base* parser::parse_close_tag()
    {
        assert(current().type == token_open_bracket);
        next();
        assert(current().type == token_slash);
        next();
        
        assert(current().type == token_string);
        string close_tag = current().text;
        next();
        
        assert(current().type == token_close_bracket);
        next();

        return tag_factory::to_tag(close_tag, attribute());
    }

    attribute parser::parse_attribute()
    {
        assert(current().type == token_quote);
        next();
        
        assert(current().type == token_string || current().type == token_number);
        string attr = current().text;
        next();

        assert(current().type == token_quote);
        next();
        return attribute(attr);
    }

    node* parser::parse()
    {
        if (current().type == token_number)
        {
            string text = current().text;
            next();
            return new node_const(text);
        }
        
        tag_base* open_tag = parse_open_tag();        
    
        list<node*> children;
        while (!end())
        {
            children.push_back(parse());
        }

        tag_base* close_tag = parse_close_tag();

        assert(open_tag->type() == close_tag->type());

        return new node_tag(open_tag, children);
    }

    parser_result parser::tree()
    {
        return parser_result {parse()};
    }

}