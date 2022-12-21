#include "Token.h"

Token::Token(std::string word, TOKEN_T type, uint32_t col, uint32_t row) : m_type(type), m_word(word), col(col), row(row) {}

std::string Token::word() const 
{
    return this->m_word;
}

TOKEN_T Token::type() const 
{
    return this->m_type;
}