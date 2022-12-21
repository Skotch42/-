#pragma once

#include <string>

enum class TOKEN_T 
{
    EMPTY_T = -2,
    ERROR_T,
    NAME_T,             // name
    CONST_INT_T,        // k
    NEWINT_T,           // int
    NEWARRAY_T,         // array
    READ_T,            //"read"
    WRITE_T,           //"write"
    L_BRACE_T,          //"{"
    R_BRACE_T,         //"}"
    L_SQUARE_T,        //"["
    R_SQUARE_T,        //"]"
    COMMA_T,            //","
    ASSIGN_T,          //"="
    LESS_T,            //"<"
    GREATER_T,         //">"
    LOREQUAL_T,        //"<="
    GOREQUAL_T,        //">="
    EQUAL_T,           //"=="
    NOTEQUAL_T,        //"!="
    IF_T,              //"if"
    ELSE_T,            //"else"
    WHILE_T,           //"while"
    PLUS_T,             //"+"
    MINUS_T,            //"-"
    MUL_T,              //"*"
    DIV_T,              //"/"
    L_PR_T,             //"("
    R_PR_T,             //")"
    END_T,              //";"
};

class Token 
{
    TOKEN_T m_type;
    std::string m_word;
public:
    Token() = default;
    Token(std::string word, TOKEN_T type, uint32_t col = 0, uint32_t row = 0);

    uint32_t col;
    uint32_t row;

    std::string word() const;
    TOKEN_T type() const;
};