#include "RPN.h"

RPSItem::RPSItem(int value, ITEM_TYPE type, TOKEN_T token_type) : value(value), type(type), token_type(token_type) {}

RPSItem::RPSItem(std::string word, ITEM_TYPE type, TOKEN_T token_type) : word(word), type(type), token_type(token_type) 
{
    switch (token_type) 
    {
    case TOKEN_T::EQUAL_T:
        operation = OPERATION_T::EQUAL_T;
        this->word = "==";
        break;
    case TOKEN_T::ASSIGN_T:
        operation = OPERATION_T::ASSIGN_T;
        this->word = "=";
        break;
    case TOKEN_T::DIV_T:
        operation = OPERATION_T::DIV_T;
        this->word = "/";
        break;
    case TOKEN_T::MINUS_T:
        operation = OPERATION_T::MINUS_T;
        this->word = "-";
        break;
    case TOKEN_T::MUL_T:
        operation = OPERATION_T::MUL_T;
        this->word = "*";
        break;
    case TOKEN_T::PLUS_T:
        operation = OPERATION_T::PLUS_T;
        this->word = "+";
        break;
    case TOKEN_T::GOREQUAL_T:
        operation = OPERATION_T::GREATER_OR_EQUAL_T;
        this->word = ">=";
        break;
    case TOKEN_T::LOREQUAL_T:
        operation = OPERATION_T::LESS_OR_EQUAL_T;
        this->word = "<=";
        break;
    case TOKEN_T::GREATER_T:
        this->word = ">";
        operation = OPERATION_T::GREATER_T;
        break;
    case TOKEN_T::LESS_T:
        operation = OPERATION_T::LESS_T;
        this->word = "<";
        break;
    case TOKEN_T::NOTEQUAL_T:
        operation = OPERATION_T::NOT_EQUAL_T;
        this->word = "!=";
        break;
    default:
        break;
    }
}

RPSItem::RPSItem(std::string word, OPERATION_T operation) : word(word), type(ITEM_TYPE::OPERATOR), operation(operation) {}

RPSItem::RPSItem(std::string word, int mark_pos) : word(word), mark_pos(mark_pos), type(ITEM_TYPE::EMPTY),operation(OPERATION_T::MARK_T) {}

RPSItem::RPSItem(std::string word, ITEM_TYPE type, int index) :  word(word), index(index), type(type) {}
