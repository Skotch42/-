#pragma once

#include <vector>
#include <string>
#include <map>
#include "Token.h"

enum class ITEM_TYPE 
{
    OPERATOR,
    VARIABLE,
    CONST,
    ARRAY_EL,
    EMPTY,
    FINAL
};

enum class OPERATION_T 
{
    BEGIN_T,
    END_T,
    MARK_T,
    DECLARE_ARR,
    READ_T,
    WRITE_T,
    ASSIGN_T,
    PLUS_T,
    MINUS_T,
    DIV_T,
    MUL_T,
    LESS_T,
    GREATER_T,
    EQUAL_T,
    LESS_OR_EQUAL_T,
    GREATER_OR_EQUAL_T,
    NOT_EQUAL_T,
    J_T,
    JF_T,
    I_T,
    ERROR_T
};

struct RPSItem 
{
    int value = -1;
    int index = -1;
    int mark_pos;
    std::string word = "";
    ITEM_TYPE type;
    TOKEN_T token_type;
    OPERATION_T operation = OPERATION_T::ERROR_T;

    RPSItem(int value, ITEM_TYPE type, TOKEN_T token_type);
    RPSItem(std::string word, ITEM_TYPE type, TOKEN_T token_type);
    RPSItem(std::string word, OPERATION_T operation);
    RPSItem(std::string word = "", int mark_pos = -1);
    RPSItem(std::string word, ITEM_TYPE type, int index);
};

struct RPN 
{
    std::vector<RPSItem> items;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> arr;
};
