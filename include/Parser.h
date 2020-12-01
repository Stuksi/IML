#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"
#include "Tag.h"

class Parser
{
private:
    Tag *currentTag;
    std::vector<Token> tokenized;
    size_t it;

    bool more();
    bool isValue();
    bool isBodyTag();
    bool isCloseTag();
    bool isLetTag();

    void next();
    void previous();
    void startExpression();
    void endExpression();

    Attribute findAttributeById(std::string);
    Token current();

    std::vector<double> parseExpression();
    std::vector<double> parseNormalExpression();
    std::vector<double> parseLetExpression();
    void parseValueExpression();
    Tag* parseOpenTag();
    Tag* parseBodyTag();
    Tag* parseCloseTag();
    Attribute parseAttribute();
public:
    Parser(std::istream&);
    void build(std::ostream&);
};

/*

Grammar:

    Expression              := NormalExpression | LetExpression | Value , [ Expression ] ;
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