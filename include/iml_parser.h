#ifndef __iml_parser_h
#define __iml_parser_h

#include "iml_tokenizer.h"
#include "iml_tag.h"
#include <stack>
#include <unordered_map>

class iml_parser
{
private:
    // Core
    std::stack<iml_tag*> hierarchy;
    std::unordered_map<std::string, std::list<double>> linked_names;
    std::list<iml_token> t_list;
    std::list<iml_token>::iterator t_list_iterator;

    // Predicates
    bool more();
    bool is_value();
    bool is_end_tag();

    // Selectors and Iterators
    void next();
    void previous();
    iml_token current();

    // Atoms
    void parse_value();
    void parse_open_tag();
    void parse_body_tag();
    void parse_close_tag();
    void parse_attribute();

    // Expressions
    void parse_expression();
    void parse_tag_expression();
    
public:
    iml_parser(std::istream&);
    void build(std::ostream&);
};

/*

Grammar:

    Expression              := TagExpression, Expression | Value , Expression | "" ;
    TagExpression           := OpenTag , Expression , [BodyTag , Expression] , CloseTag ;
    OpenTag                 := "<" , String , [ Attribute ] , ">" ;
    EndTag                  := BodyTag | CloseTag
    BodyTag                 := "<" , "BODY" , "/" , ">" ;
    CloseTag                := "<" , "/" , String , ">" ; 
    Attribute               := """ , Value , """ ;
    Value                   := RealNumber | String ;
    RealNumber              := ( "0" | [ "-" ] , DigitNoZero , { Digit } ) , [ "." , Digit , { Digit } ] ;
    String                  := Char , { Char } ;
    Digit                   := "0" | DigitNoZero ;
    Char                    := "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "-";
    DigitNoZero             := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

Symbols:
    :=         --->         definition
    ,          --->         concatenation
    |          --->         alternation
    [...]      --->         optional
    {...}      --->         repetition
    "..."      --->         terminal string
    ;          --->         termination

*/

#endif