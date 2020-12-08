#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"
#include "../Base Tag Classes/Tag.h"
#include "../../lib/Stack.h"
#include "../../lib/HashTable.h"
#include "../../lib/DLList.h"


class Parser
{
private:
    // Core
    Stack<Tag*> hierarchy;
    HashTable<std::string, DLList<double>> nameLinks;
    DLList<Token> tokenList;
    DLList<Token>::Iterator tokenListIterator;

    // Predicates
    bool hasMoreTokens();
    bool isValue();
    bool isEndTag();

    // Selectors and Iterators
    void next();
    void previous();
    Token current();

    // Atoms
    void parseValue();
    void parseOpenTag();
    void parseBodyTag();
    void parseCloseTag();
    void parseAttribute();

    // Expressions
    void parseExpression();
    void parseTagExpression();
    
public:
    Parser(std::istream&);
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