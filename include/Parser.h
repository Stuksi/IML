#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"
#include "Tag.h"
#include <stack>

class Parser
{
private:
    // Core
    std::stack<Tag*> hierarchy;
    std::vector<Token> tokenized;
    size_t it;

    // Predicates
    bool more();
    bool isValue();
    bool isLetTag();
    bool isBodyTag();
    bool isCloseTag();

    // Selectors and Iterators
    void next();
    void previous();
    Token current();

    // Functionalities
    void moveValuesToAttribute();
    Attribute searchAttributeInHierarchy(std::string);

    // Atoms
    void parseValue();
    void parseOpenTag();
    void parseBodyTag();
    void parseCloseTag();
    Attribute parseAttribute();

    // Expressions
    void parseExpression();
    void parseLetExpression();
    void parseNormalExpression();
    
public:
    Parser(std::istream&);
    void build(std::ostream&);
};

/*

Grammar:

    Expression              := NormalExpression , Expression | LetExpression , Expression | Value , Expression | "" ;
    NormalExpression        := OpenTag , Expression , CloseTag ;
    LetExpression           := OpenTag , Expression , BodyTag , Expression , CloseTag ;
    OpenTag                 := "<" , String , [ Attribute ] , ">" ;
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