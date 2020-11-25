#include "../include/iml_tokenizer.h"

#include <string.h>

iml_tokenizer::iml_tokenizer(std::istream& _in) : in(_in)
{}

bool iml_tokenizer::is_text()
{
    return (cursor >= 'A' && cursor <= 'Z') || cursor == '-';
}

bool iml_tokenizer::is_digit()
{
    return cursor >= '0' && cursor <= '9';
}

char* iml_tokenizer::append_text(char*& buffer)
{
    size_t buffer_size = strlen(buffer);
    char* _buffer = new char[buffer_size + 2];
    strcpy(_buffer, buffer);
    delete buffer;
    _buffer[buffer_size++] = cursor;
    _buffer[buffer_size] = '\0';
    return _buffer; 
}

char* iml_tokenizer::read_text()
{
    char* buffer = nullptr;
    while (is_text())
    {
        buffer = append_text(buffer);
        next();
    }
    return buffer;
}

double iml_tokenizer::read_number()
{
    double num = 0;
    while (is_digit())
    {
        num = num * 10 + cursor - '0';
        next();
    }
    return num;
}

void iml_tokenizer::clear_white_spaces()
{
    while (in.peek() == ' ' || in.peek() == '\n')
    {
        in.get();
    }
}

void iml_tokenizer::next()
{
    clear_white_spaces();
    cursor = in.peek();
    in.get();
}

iml_token iml_tokenizer::next_token()
{
    if(cursor == '<')
    {
        return iml_token {open_bracket, "<", 0};
    }
    else if(cursor == '>')
    {
        return iml_token {close_bracket, ">", 0};
    }
    else if(cursor == '/')
    {
        return iml_token {slash, "/", 0};
    }
    else if(cursor == '"')
    {
        return iml_token {quote, "\"", 0};
    }
    else if(cursor == '-')
    {
        return iml_token {minus, "-", 0};
    }
    else if(is_text())
    {
        return iml_token {text, read_text(), 0};
    }
    else if(is_digit())
    {
        return iml_token {number, "?", read_number()};
    }
    return iml_token {error, "?", 0};
}

iml_tokenizer_result iml_tokenizer::tokenize()
{
    iml_tokenizer_result result;
    while (in)
    {
        next();
        result.tokens.append(next_token());
    }
    return result;
}