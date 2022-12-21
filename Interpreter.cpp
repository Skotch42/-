#include "Interpreter.h"
#include <utility>
#include <iostream>
#include "Errors.h"

void Interpreter::push_item(RPSItem& item, std::stack<RPSItem>& stack) 
{
    stack.push(item);
}

void Interpreter::generate_commands() 
{
    while (pos < items.size()) 
    {
        step(st, items[pos]);

        if (!from_jump)
            pos++;

        from_jump = false;
    }
}

void Interpreter::step(std::stack<RPSItem>& stack, RPSItem item)
{
    if (item.type != ITEM_TYPE::FINAL) 
    {
        if (item.type != ITEM_TYPE::OPERATOR) 
        {
            push_item(item, stack);
        } 
        else 
            if (item.operation == OPERATION_T::WRITE_T || item.operation == OPERATION_T::READ_T || item.operation == OPERATION_T::J_T) 
            {
                auto a = stack.top();
                stack.pop();
                execute_un_command(a, item.operation);
            }
            else 
                if (item.operation == OPERATION_T::MARK_T)
                    return;
                else 
                    if (item.operation == OPERATION_T::BEGIN_T || item.operation == OPERATION_T::END_T)
                    {
                        return;
                    } 
                    else 
                    {
                        auto rvalue = stack.top();
                        stack.pop();
                        auto lvalue = stack.top();
                        stack.pop();
                        execute_bin_command(lvalue, rvalue, item.operation);
                    }
    }
}

void Interpreter::execute_un_command(RPSItem lvalue, OPERATION_T operation) 
{
    switch(operation) 
    {

    case OPERATION_T::WRITE_T:
        std::cout << "\n";
        if (lvalue.type == ITEM_TYPE::CONST) 
        {
            std::cout << lvalue.value;
        } 
        else 
            if (lvalue.type == ITEM_TYPE::VARIABLE) 
            {
            std::cout << vars.at(lvalue.word);
            } 
            else 
                if (lvalue.type == ITEM_TYPE::ARRAY_EL) 
                {
                    std::cout << arrs.at(lvalue.word)[lvalue.index];
                }
        break;

    case OPERATION_T::READ_T:
        std::cout << "\n>>";
        if (lvalue.type == ITEM_TYPE::CONST) 
        {
            std::cin >> lvalue.value;
        } 
        else 
            if (lvalue.type == ITEM_TYPE::VARIABLE) 
            {
                std::cin >> vars.at(lvalue.word);
            } 
            else 
                if (lvalue.type == ITEM_TYPE::ARRAY_EL) 
                {
                    std::cin >> arrs.at(lvalue.word)[lvalue.index];
                }
        break;

    case OPERATION_T::J_T:
        from_jump = true;
        pos = lvalue.mark_pos;
        break;

    default:
        break;
    }
}

void Interpreter::execute_bin_command(RPSItem lvalue, RPSItem rvalue, OPERATION_T operation) 
{
    int index = 0, size = 0;
    std::string name;

    switch(operation) 
    {
        case OPERATION_T::MUL_T:
        case OPERATION_T::PLUS_T:
        case OPERATION_T::DIV_T:
        case OPERATION_T::MINUS_T:
            do_arithm(lvalue, rvalue, operation);
            break;

        case OPERATION_T::ASSIGN_T:
            do_assign(lvalue, rvalue);
            break;

        case OPERATION_T::DECLARE_ARR:
            if (rvalue.type == ITEM_TYPE::CONST)
            {
                size = rvalue.value;
            }
            else 
                throw RuntimeError("Expected const integer!");
            name = lvalue.word;
            mem_alloc(size, name);
            break;

        case OPERATION_T::I_T:
            if (rvalue.type == ITEM_TYPE::CONST)
            {
                index = rvalue.value;
            }
            else 
                if (rvalue.type == ITEM_TYPE::VARIABLE)
                {
                    index = vars.at(rvalue.word);
                }
                else 
                    if (rvalue.type == ITEM_TYPE::ARRAY_EL)
                    {
                        index = arrs.at(rvalue.word)[rvalue.index];
                    }
            st.push(RPSItem(lvalue.word, ITEM_TYPE::ARRAY_EL, index));
            break;

        case OPERATION_T::GREATER_T:
        case OPERATION_T::LESS_T:
        case OPERATION_T::GREATER_OR_EQUAL_T:
        case OPERATION_T::EQUAL_T:
        case OPERATION_T::NOT_EQUAL_T:
        case OPERATION_T::LESS_OR_EQUAL_T:
            do_compare(lvalue, rvalue, operation);
            break;

        case OPERATION_T::JF_T:
            if (lvalue.value == 0) 
            {
                pos = rvalue.mark_pos;
                from_jump = true;
            }

        default:
            break;
    }
}

std::tuple<int,int> Interpreter::get_values(RPSItem lvalue, RPSItem rvalue) 
{
    int lval, rval;
    if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == ITEM_TYPE::CONST) {
        lval = lvalue.value;
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::CONST) {
        lval = vars.at(lvalue.word);
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == ITEM_TYPE::VARIABLE) {
        lval = lvalue.value;
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::CONST) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::VARIABLE) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::CONST && rvalue.type == ITEM_TYPE::ARRAY_EL) {
        lval = lvalue.value;
        rval = arrs.at(rvalue.word)[rvalue.index];
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::ARRAY_EL) {
        lval = vars.at(lvalue.word);
        rval = arrs.at(rvalue.word)[rvalue.index];
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::VARIABLE) {
        lval = vars.at(lvalue.word);
        rval = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::ARRAY_EL) {
        lval = arrs.at(lvalue.word)[lvalue.index];
        rval = arrs.at(rvalue.word)[rvalue.index];
    }
    return 
    { 
        lval, rval 
    };
}

void Interpreter::do_compare(RPSItem lvalue, RPSItem rvalue, OPERATION_T operation) 
{
    RPSItem sum(0, ITEM_TYPE::CONST, TOKEN_T::CONST_INT_T);
    st.push(sum);
    int lval, rval;
    auto values = get_values(lvalue, rvalue);
    lval = std::get<0>(values);
    rval = std::get<1>(values);

    switch(operation)
    {
        case OPERATION_T::GREATER_T:
            st.top().value = lval > rval ? 1 : 0;
            break;

        case OPERATION_T::LESS_T:
            st.top().value = lval < rval ? 1 : 0;
            break;

        case OPERATION_T::GREATER_OR_EQUAL_T:
            st.top().value = lval >= rval ? 1 : 0;
            break;

        case OPERATION_T::EQUAL_T:
            st.top().value = lval == rval ? 1 : 0;
            break;

        case OPERATION_T::NOT_EQUAL_T:
            st.top().value = lval != rval ? 1 : 0;
            break;

        case OPERATION_T::LESS_OR_EQUAL_T:
            st.top().value = lval <= rval ? 1 : 0;
            break;

        default:
            break;
    }
}

void Interpreter::mem_alloc(int size, std::string name) 
{
    arrs.at(name).resize(size);
}

void Interpreter::do_assign(RPSItem lvalue, RPSItem rvalue) 
{
    if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::VARIABLE)
        vars.at(lvalue.word) = vars.at(rvalue.word);
    else if(lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::CONST) {
        vars.at(lvalue.word) = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::CONST) {
        arrs.at(lvalue.word)[lvalue.index] = rvalue.value;
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::VARIABLE) {
        arrs.at(lvalue.word)[lvalue.index] = vars.at(rvalue.word);
    } else if (lvalue.type == ITEM_TYPE::VARIABLE && rvalue.type == ITEM_TYPE::ARRAY_EL) {
        vars.at(lvalue.word) = arrs.at(rvalue.word)[rvalue.index];
    } else if (lvalue.type == ITEM_TYPE::ARRAY_EL && rvalue.type == ITEM_TYPE::ARRAY_EL)
        arrs.at(lvalue.word)[lvalue.index] = arrs.at(rvalue.word)[rvalue.index];
}

void Interpreter::do_arithm(RPSItem lvalue, RPSItem rvalue, OPERATION_T operation) 
{
    RPSItem sum(0, ITEM_TYPE::CONST, TOKEN_T::CONST_INT_T);
    st.push(sum);
    int lval, rval;
    auto values = get_values(lvalue, rvalue);
    lval = std::get<0>(values);
    rval = std::get<1>(values);

    switch (operation)
    {
    case OPERATION_T::MUL_T:
        st.top().value = lval * rval;
        break;

    case OPERATION_T::PLUS_T:
        st.top().value = lval + rval;
        break;

    case OPERATION_T::MINUS_T:
        st.top().value = lval - rval;
        break;

    case OPERATION_T::DIV_T:
        if (rval == 0)
            throw RuntimeError("Error!");
        else st.top().value = lval / rval;  //exception!
        break;

    default:
        break;
    }
}