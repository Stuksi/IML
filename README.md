# [iml](https://docs.google.com/document/d/1MXNOaWoTIxODs8LzAuqIOLq4j4mkw4ZweVLvbJe6XKs/edit)

### What is iml?
iml is a light weight C++ language interpreting/parsing library. It consists of a fast interpreting/parsing mechanism. The IML language is inspired by an uni data structutes project. It is easy to develop new tags, and its very easy to integrate and use the library.

### What is its purpose?
IML as a language can be used to evaluate mathematical expressions with the use of tags or to structure arrays which can be used with other programs. iml provides a small range of tags to be played with.

### IML Grammar
The parser and the interpreter are based on the following grammar:
```
    expression              := (tag_expression | value) , expression | "" ;
    tag_expression          := open_tag , expression , [let_tag_expression] , close_tag ;
    let_tag_expreesion      := body_tag , expression
    open_tag                := "<" , string , [ attribute ] , ">"
    body_tag                := "<" , "BODY" , "/" , ">" ;
    close_tag               := "<" , "/" , string , ">" ; 
    attribute               := """ , value , """ ;
    value                   := double | string ;
```

### How to use it?
Every element is stored in the iml namespace, so to use the library, add `iml::` in front of the class elements or simply write 
`using namespace iml;` on top of your program.

### Quick start guide...
Simply install the library and add the interpreter (parser) header file in your project.
You can try the examples in the 'examples' directory.. They consist of an example with the interpreter and the parser:

#### Interpreter example
```
    iml::interpreter i;
    i.interpret_file("iml_file_example.iml");
```

#### Parser example
```
    iml::parser parser;
    iml::parser_result result = parser.build_tree("iml_file_example.iml");
    result.evaluate();
    result.visualize();
```

### Installation
[Version 1.1](https://github.com/Stuksi/iml/releases/download/v1.1/v1.1.zip)