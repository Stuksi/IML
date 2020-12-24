#ifndef HEADER_PARSER_H
#define HEADER_PARSER_H

// STL headers
#include <iostream>
#include <string>
#include <stack>
#include <list>

// STD namespace
using namespace std;

// The iml namespace
namespace iml
{
    // Node types
    enum node_type
    {
        node_null,
        node_document,
        node_element
    };

    // Token types
    enum token_type
    {
        token_invalid,
        token_number,
        token_string,
        token_open_bracket,
        token_close_bracket,
        token_slash,
        token_quote
    };

    // Tag types
    enum tag_type
    {
        tag_null,
        tag_map_inc,
        tag_map_mlt,
        tag_agg_sum,
        tag_agg_pro,
        tag_agg_avg,
        tag_agg_fst,
        tag_agg_lst,
        tag_srt_rev,
        tag_srt_ord,
        tag_srt_slc,
        tag_srt_dst,
        tag_let,
        tag_body
    };

    // Forward declarations
    class attribute; // Attribute

    class node; // Node
    class node_const;
    class node_tag;
    class node_iterator;

    class tag_base; // Tag
    class taga_base;
    struct tag_factory; 
    template <tag_type T>
    class tag;
    template <tag_type T>
    class taga;

    class lexer; // Lexer
    struct lexer_result;
    struct token;

    class parser; // Parser
    struct parser_result;

    // Attribute class
    class attribute
    {
    private:
        string value_;
    public:
        attribute();
        attribute(string);

        bool empty() const;

        string value() const;

        double as_number() const;
    };

    // Abstract base node class
    class node
    {
    private:
        node_type type_;
    public:
        node();
        node(node_type);
        virtual ~node();

        node_type type() const;

        // node_iterator begin();
        // node_iterator end();
 
        virtual void visualize(ostream&) const = 0;
        virtual list<double> evaluate() const = 0;
    };

    // Node const 
    class node_const : public node
    {
    private:
        double value_;
    public:
        node_const();
        node_const(string);
        ~node_const();
        
        void visualize(ostream&) const;
        list<double> evaluate() const;
    };

    // Node tag 
    class node_tag : public node
    {
    private:
        tag_base* tag_;
        list<node*> children_;
    public:
        node_tag();
        node_tag(tag_base*, list<node*>);
        ~node_tag();

        void visualize(ostream&) const;
        list<double> evaluate() const;
    };

    // Node tag 
    // class node_identificator : public node
    // {
    // private:
    //     tag_base* tag_;
    //     list<node*> identificator_children_;
    //     list<node*> children_;
    // public:
    //     node_identificator();
    //     node_identificator(tag_base*, list<node*>, list<node*>);
    //     ~node_identificator();

    //     void visualize(ostream&) const;
        
    //     list<double> evaluate() const;
    // };

    // Node iterator
    // class node_iterator 
    // {
    // private:
    //     stack<node*&> node_stack;
    // public:

    //     node_iterator(node*&);

    //     node*& operator*();

    //     node_iterator& operator++();
        
    //     bool operator!=(const node_iterator&);
    // };

    // Abstract base tag class
    class tag_base
    {
    private:
        tag_type type_;
    public:

        tag_base();

        tag_base(tag_type);

        virtual ~tag_base();

        tag_type type() const;

        string as_string() const;

        virtual attribute attr() const;

        virtual list<double> apply(const list<double>&) const = 0;
    };

    // Abstract base attribute tag class
    class taga_base : public tag_base
    {
    private:
        attribute attribute_;
    public:
        taga_base();

        taga_base(tag_type, attribute);

        virtual ~taga_base();

        attribute attr() const;

        virtual attribute configure(attribute) const = 0;

        virtual list<double> apply(const list<double>&) const = 0;
    };

    struct tag_factory
    {
        static tag_base* to_tag(string, attribute);
    };

    class lexer
    {
    private:
        istream& in_;
        token next();
    public:
        lexer(istream&);
        lexer_result tokenize();
    };

    struct lexer_result
    {
        list<token> tokens;
    };

    struct token
    {
        string text;
        token_type type;
    };

    class parser
    {
    private:
        list<token> tokens_;
        list<token>::iterator tokens_iterator_;
        
        token current() const;
        void next();
        void previous();
        bool end();

        tag_base* parse_open_tag();
        tag_base* parse_close_tag();
        attribute parse_attribute();

        node* parse();
    public:
        parser(istream&);
        parser_result tree();
    };

    struct parser_result
    {
        node* root;
    };

    // Template tag class
    template <tag_type T>
    class tag : public tag_base
    {
    public:
        tag();
        ~tag();
        list<double> apply(const list<double>&) const;
    };

    // Template attribute tag class
    template <tag_type T>
    class taga : public taga_base
    {
    public:
        taga();
        taga(attribute);
        ~taga();
        attribute configure(attribute) const;
        list<double> apply(const list<double>&) const;
    };

    template <tag_type T>
    tag<T>::tag() : tag_base(T)
    {}

    template <tag_type T>
    tag<T>::~tag()
    {}

    template <tag_type T>    
    list<double> tag<T>::apply(const list<double>& values) const
    {
        return values;
    }
    
    template <tag_type T>
    taga<T>::taga()
    {}

    template <tag_type T>
    taga<T>::taga(attribute attr) : taga_base(T, attr)
    {}

    template <tag_type T>
    taga<T>::~taga()
    {}
        
    template <tag_type T>    
    list<double> taga<T>::apply(const list<double>& values) const
    {
        return values;
    }

    template <tag_type T>
    attribute taga<T>::configure(attribute attr) const
    {
        return attr;
    }

}

#endif