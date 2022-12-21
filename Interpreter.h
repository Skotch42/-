#pragma once

#include <string>
#include <vector>
#include <stack>
#include <map>
#include "RPN.h"

class Interpreter 
{
    size_t pos = 0;
    std::map<std::string, int> vars;
    std::map<std::string, std::vector<int>> arrs;
    std::vector<RPSItem> items;
    std::stack<RPSItem> st;
    bool from_jump = false;
    RPSItem sum = RPSItem(0, ITEM_TYPE::CONST, TOKEN_T::CONST_INT_T);

    void mem_alloc(int, std::string);
    void push_item(RPSItem&, std::stack<RPSItem>&);
    void execute_bin_command(RPSItem,RPSItem, OPERATION_T operation);
    void execute_un_command(RPSItem, OPERATION_T operation);
    void step(std::stack<RPSItem>&, RPSItem);
    void do_arithm(RPSItem, RPSItem,OPERATION_T);
    void do_assign(RPSItem, RPSItem);
    void do_compare(RPSItem, RPSItem, OPERATION_T);
    std::tuple<int,int> get_values(RPSItem lvalue, RPSItem rvalue);

public:
    void generate_commands();
    Interpreter(RPN ops) : vars(ops.vars), arrs(ops.arr), items(ops.items){};
};
