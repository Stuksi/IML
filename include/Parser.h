#ifndef __Parser_H
#define __Parser_H

#include "Tokenizer.h"

class Parser
{
private:
    std::vector<Token> tokenized;
    size_t it;

    void next();
    void previous();
    Token current();

public:
    Parser(std::istream&);
};

/*

Grammar:

    Expression := OpenTag , { Expression | RealNumber | String } , CloseTag ;
    OpenTag := "<" , String , [ Attribute ] , ">" ;
    CloseTag := "<" , "/" , String , ">" ; 
    Attribute := """ , RealNumber | String , """ ;
    RealNumber := IntegerNumber , [ "." , Digit , { Digit } ] ;
    IntegerNumber := "0" | [ "-" ] , NaturalNumber ;
    NaturalNumber := DigitNoZero , { Digit } ;
    String := Char , { Char } ;
    Digit := "0" | DigitNoZero ;
    Char := "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | 
            "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" ;
    DigitNoZero := "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

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