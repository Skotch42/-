#pragma once

#include <string>
#include <vector>
#include "Token.h"

class Tokenizer
{
public:

    using SemanticFunction = bool(Tokenizer::*)(char);
    Tokenizer(std::string &text);
    Token getToken();
    bool empty();

private:
    static const SemanticFunction SEMANTIC_FUNCTION[19];

    std::string m_text;
    uint32_t m_textPos = 0;
    uint32_t m_row = 0;
    uint32_t m_column = 0;
    std::string m_accumulatedString = "";
    int64_t m_accumulatedNumber = 0;
    TOKEN_T m_tokenType;

    bool f1(char), f2(char), f3(char), f4(char), f5(char),
         f6(char), f7(char), f8(char), f9(char), f10(char),
        f11(char), f12(char), f13(char), f14(char), f15(char),
        f16(char), f17(char), f18(char), f19(char);
};