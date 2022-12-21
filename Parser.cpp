#include "Parser.h"
#include "Errors.h"

#define p Parser

const p::functionalArray p::funcArr[47] = 
{
   &p::f1, &p::f2, &p::f3, &p::f4, &p::f5, &p::f6, &p::f7, &p::f8, &p::f9,
   &p::f10, &p::f11,
   &p::f12, &p::f13, &p::f14, &p::f15, &p::f16, &p::f17, &p::f18, &p::f19,
   &p::f20, &p::f21,
   &p::f22, &p::f23, &p::f24, &p::f25, &p::f26, &p::f27, &p::f28, &p::f29,
   &p::f30, &p::f31,
   &p::f32, &p::f33, &p::f34, &p::f35, &p::f36, &p::f37, &p::f38, &p::f39,
   &p::f40, &p::f41, &p::f42, &p::f43, &p::f44, &p::f45, &p::f46, &p::f47
};

const int Parser::M[17][28] = 
{
    {2,  0,  3,  4,  5,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  0,  8,  0,  0,  0,  0,  0,  0,  46},
    {10, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  11, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
    {12, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  13, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  9},
    {14, 1,  1,  1,  15, 16, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  7,  1,  8,  1,  1,  1,  1,  1,  1,  1},
    {17, 1,  1,  1,  18, 19, 1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  20, 1,  21, 1,  1,  1,  1,  1,  1,  1},
    {1,  1,  1,  1,  1,  1,  1,  1,  47,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1},
    {22, 23, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  24, 0,  0},
    {0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  25, 26, 27, 28, 29, 30, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    {45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 45, 31, 45, 45, 45, 45, 45, 45, 45, 45},
    {32, 33, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  34, 0,  0},
    {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  35, 36, 1,  1,  1,  1,  1},
    {37, 38, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  39, 0,  0},
    {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  40, 41, 1,  1,  1},
    {42, 43, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  44, 0,  0},
    {1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1}
};

Parser::Parser(Tokenizer& t) : m_tokenizer(t) 
{
    reset();
}

void Parser::executeSemantic(std::stack<StackItem>& stack2) 
{
    auto word = stack2.top().word();
    auto m_size = marks.size();

    if (word == "<1>") 
    {
        marks.push(k);
        cur_ops.items.emplace_back(RPSItem(std::string("m")+ std::to_string(m_size)));
        cur_ops.items.emplace_back(RPSItem("JF", OPERATION_T::JF_T));
        count();
        count();
    } 
    else 
        if (word == "<2>") 
        {
        cur_ops.items[marks.top()].mark_pos = k + 2;
        marks.pop();
        marks.push(k);
        cur_ops.items.emplace_back(RPSItem(std::string("m")+ std::to_string(m_size)));
        cur_ops.items.emplace_back(RPSItem("J",OPERATION_T::J_T));
        count();
        count();
        } 
        else 
            if (word == "<3>") 
            {
            cur_ops.items[marks.top()].mark_pos = k;
            marks.pop();
            } 
            else 
                if (word == "<4>") 
                {
                marks.push(k);
                }
                else 
                    if (word == "<5>") 
                    {
                    cur_ops.items[marks.top()].mark_pos = k + 2;
                    marks.pop();
                    cur_ops.items.emplace_back(RPSItem(std::string("m")+ std::to_string(m_size), marks.top()));
                    marks.pop();
                    cur_ops.items.emplace_back(RPSItem("J",OPERATION_T::J_T));
                    count();
                    count();
                    }
                    else 
                        if (word == "<11>") 
                        {
                        is_filling_vars = true;
                        }
                        else 
                            if (word == "<12>") 
                            {
                                is_filling_arr = true;
                            }
                            else 
                                if (word == "<16>") 
                                {
                                    if (is_filling_vars) 
                                    {
                                        if (cur_ops.vars.find(token_word) == cur_ops.vars.end())
                                        {
                                            cur_ops.vars.insert(make_pair(token_word, 0));
                                        }
                                        else
                                        {
                                            throw DeclarationError(token);
                                        }
                                    }
                                    if (is_filling_arr)
                                    {
                                        cur_ops.items.push_back(RPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T));
                                        count();

                                        if (cur_ops.arr.find(token_word) == cur_ops.arr.end())
                                        {
                                            cur_ops.arr.insert(make_pair(token_word, std::vector<int>()));
                                        } 
                                        else
                                        {
                                            throw DeclarationError(token);
                                        }
                                    }
                                }
                                else 
                                    if (word == "<m1>") 
                                    {
                                    cur_ops.items.emplace_back(RPSItem("DECLARE_ARR",OPERATION_T::DECLARE_ARR));
                                    count();
                                    }
                                else 
                                        if (word == "<e_declare>") 
                                        {
                                            is_filling_vars = false;
                                            is_filling_arr = false;
                                        }
                                        else 
                                            if (word == "<r>")
                                            {
                                                cur_ops.items.emplace_back(RPSItem("READ",OPERATION_T::READ_T));
                                                count();
                                            }
                                            else 
                                                if (word == "<w>")
                                                {
                                                    cur_ops.items.emplace_back(RPSItem("WRITE",OPERATION_T::WRITE_T));
                                                    count();
                                                }
                                                else 
                                                    if (word == "<i>") 
                                                    {
                                                        cur_ops.items.emplace_back(RPSItem("INDEX",OPERATION_T::I_T));
                                                        count();
                                                    }
}

bool Parser::isSemantic(std::stack<StackItem>& stack2) 
{
    auto word = stack2.top().word();

    if (word == "<1>" || word == "<2>" || word == "<3>" || word == "<4>"
        || word == "<5>" || word == "<m1>" || word == "<11>" ||word == "<e_declare>"
        || word == "<12>" || word == "<16>" || word == "<w>" || word == "<r>" || word == "<i>") 
    {
        return true;
    } 
    else
    {
        return false;
    }
}

void Parser::count() 
{
    k++;
}

void Parser::reset() 
{
    stack1.push(StackItem(P));

    stack2.push(StackItem());
    token = getToken();
}

Token Parser::getToken() 
{
    if(m_tokenizer.empty())
    {
        throw SyntaxError(token);
    }

    Token cur_token = m_tokenizer.getToken();

    token_word = cur_token.word();
    token_type = cur_token.type();

    if (token_type == TOKEN_T::ERROR_T) 
    {
        throw IllegalCharacter(cur_token);
    }

    return cur_token;
}

void Parser::step(STACK_ITEM_T top1_item_type, STACK_ITEM_T top2_item_type) 
{
    if (top2_item_type != STACK_ITEM_T::EMPTY_T) 
    {
        TOKEN_T top2_type = stack2.top().type();

        switch (top2_type) 
        {
            case TOKEN_T::CONST_INT_T:
                if (token_type == TOKEN_T::CONST_INT_T) 
                {
                    count();
                    cur_ops.items.push_back(RPSItem(std::stoi(token_word), ITEM_TYPE::CONST, TOKEN_T::CONST_INT_T));
                } 
                else
                    throw SyntaxError(token);
                break;

            case TOKEN_T::NAME_T:
                if (token_type == TOKEN_T::NAME_T) 
                {
                    count();
                    cur_ops.items.push_back(RPSItem(token_word, ITEM_TYPE::VARIABLE, TOKEN_T::NAME_T));
                } 
                else
                    throw SyntaxError(token);
                break;

            default:
                if (isSemantic(stack2)) 
                {
                    executeSemantic(stack2);
                } 
                else 
                {
                    cur_ops.items.push_back(RPSItem(stack2.top().word(), ITEM_TYPE::OPERATOR, stack2.top().type()));
                    count();
                }
        }
    }

    stack2.pop();

    switch (top1_item_type) 
    {
        default:
            stack1.pop();
            break;

        case STACK_ITEM_T::TERM_T:
            if (stack1.top().type() == token_type) 
            {
                if (!m_tokenizer.empty())
                    token = getToken();
            } 
            else
                throw SyntaxError(token);  //когда ожидалась другая лексема
            stack1.pop();
            break;

        case STACK_ITEM_T::STATE_T:
            STATE cur_state = stack1.top().get_state();
            auto cur_type = (int)token.type();
            if (cur_state >= 0) 
            {
                if (cur_type >= 0) 
                {
                    int func_num = M[cur_state][cur_type];

                    if (func_num > 0) 
                    {
                        (this->*funcArr[func_num - 1])();
                    } 
                    else
                        throw SyntaxError(token);//грамматическая ошибка
                } 
                else
                    throw SyntaxError(token);
            } 
            else throw SyntaxError(token);
    }
}

RPN Parser::make_ops() 
{
    while (!m_tokenizer.empty() || (!stack2.empty() && !stack1.empty()))
    {
        STACK_ITEM_T top1_item_type;
        STACK_ITEM_T top2_item_type;

        if (!stack1.empty())
        {
            top1_item_type = stack1.top().get_stack_item_type();
        }
        else
        {
            throw SyntaxError(token);// stack1 empty error!
        }

        if (!stack2.empty())
        {
            top2_item_type = stack2.top().get_stack_item_type();
        }
        else
        {
            throw SyntaxError(token); // stack2 empty error!
        }

        step(top1_item_type, top2_item_type);
    }

    cur_ops.items.emplace_back(RPSItem("_|_", ITEM_TYPE::FINAL, TOKEN_T::END_T));
    return cur_ops;
}

void Parser::f1() 
{
    stack1.pop();
}

void Parser::f2() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::ASSIGN_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::ASSIGN_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f3() 
{
    stack1.pop();
    stack1.push(StackItem(P));
    stack1.push(StackItem(I));
    stack1.push(StackItem(TOKEN_T::NEWINT_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<11>", TOKEN_T::EMPTY_T));
}

void Parser::f4() 
{
    stack1.pop();
    stack1.push(StackItem(P));
    stack1.push(StackItem(A));
    stack1.push(StackItem(TOKEN_T::NEWARRAY_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<12>",TOKEN_T::EMPTY_T));
}

void Parser::f5() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::READ_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<r>"));
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f6() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::WRITE_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<w>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f7() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(Z));
    stack1.push(StackItem(K));
    stack1.push(StackItem(TOKEN_T::R_BRACE_T));
    stack1.push(StackItem(Q));
    stack1.push(StackItem(S));
    stack1.push(StackItem(TOKEN_T::L_BRACE_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(C));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::IF_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<1>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f8() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::R_BRACE_T));
    stack1.push(StackItem(Q));
    stack1.push(StackItem(S));
    stack1.push(StackItem(TOKEN_T::L_BRACE_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(C));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::WHILE_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<5>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<1>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<4>"));
}

void Parser::f9() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));

    stack2.push(StackItem("<e_declare>"));

}

void Parser::f10() 
{
    stack1.pop();
    stack1.push(StackItem(STATE::M));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<16>"));
}

void Parser::f11() 
{
    stack1.pop();
    stack1.push(StackItem(STATE::M));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::COMMA_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<16>"));
    stack2.push(StackItem());
}

void Parser::f12() 
{
    stack1.pop();
    stack1.push(StackItem(N));
    stack1.push(StackItem(TOKEN_T::R_SQUARE_T));
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));
    stack1.push(StackItem(TOKEN_T::L_SQUARE_T));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<m1>"));
    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
    stack2.push(StackItem());
    stack2.push(StackItem("<16>"));
}

void Parser::f13() 
{
    stack1.pop();
    stack1.push(StackItem(N));
    stack1.push(StackItem(TOKEN_T::R_SQUARE_T));
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));
    stack1.push(StackItem(TOKEN_T::L_SQUARE_T));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::COMMA_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<m1>"));
    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
    stack2.push(StackItem());
    stack2.push(StackItem("<16>"));
    stack2.push(StackItem());
}

void Parser::f14() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::ASSIGN_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::ASSIGN_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f15() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::READ_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<r>"));
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f16() 
{
    stack1.pop();
    stack1.push(StackItem(Q));
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::WRITE_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<w>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f17() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::ASSIGN_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));


    stack2.push(StackItem(TOKEN_T::ASSIGN_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f18() 
{

    stack1.pop();
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::READ_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<r>"));
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f19() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::WRITE_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<w>"));
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f20() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(K));
    stack1.push(StackItem(TOKEN_T::R_BRACE_T));
    stack1.push(StackItem(Q));
    stack1.push(StackItem(S));
    stack1.push(StackItem(TOKEN_T::L_BRACE_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(C));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::IF_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<1>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f21() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::R_BRACE_T));
    stack1.push(StackItem(Q));
    stack1.push(StackItem(S));
    stack1.push(StackItem(TOKEN_T::L_BRACE_T));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(C));
    stack1.push(StackItem(TOKEN_T::L_PR_T));
    stack1.push(StackItem(TOKEN_T::WHILE_T));

    stack2.push(StackItem("<5>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<1>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<4>"));
}

void Parser::f22() 
{
    stack1.pop();
    stack1.push(StackItem(D));
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f23() 
{
    stack1.pop();
    stack1.push(StackItem(D));
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
}

void Parser::f24() 
{
    stack1.pop();
    stack1.push(StackItem(D));
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f25() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::LESS_T));

    stack2.push(StackItem(TOKEN_T::LESS_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f26() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::GREATER_T));

    stack2.push(StackItem(TOKEN_T::GREATER_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f27() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::LOREQUAL_T));

    stack2.push(StackItem(TOKEN_T::LOREQUAL_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f28() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::GOREQUAL_T));

    stack2.push(StackItem(TOKEN_T::GOREQUAL_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f29() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::EQUAL_T));

    stack2.push(StackItem(TOKEN_T::EQUAL_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f30() 
{
    stack1.pop();
    stack1.push(StackItem(Z));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::NOTEQUAL_T));

    stack2.push(StackItem(TOKEN_T::NOTEQUAL_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f31() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::R_BRACE_T));
    stack1.push(StackItem(Q));
    stack1.push(StackItem(S));
    stack1.push(StackItem(TOKEN_T::L_BRACE_T));
    stack1.push(StackItem(TOKEN_T::ELSE_T));

    stack2.push(StackItem());
    stack2.push(StackItem("<3>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem("<2>"));
}

void Parser::f32() 
{
    stack1.pop();
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f33() 
{
    stack1.pop();
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
}

void Parser::f34() 
{
    stack1.pop();
    stack1.push(StackItem(U));
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f35() 
{
    stack1.pop();
    stack1.push(StackItem(U));
    stack1.push(StackItem(T));
    stack1.push(StackItem(TOKEN_T::PLUS_T));

    stack2.push(StackItem(TOKEN_T::PLUS_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f36() 
{
    stack1.pop();
    stack1.push(StackItem(U));
    stack1.push(StackItem(T));
    stack1.push(StackItem(TOKEN_T::MINUS_T));

    stack2.push(StackItem(TOKEN_T::MINUS_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f37() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(H));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));

}

void Parser::f38() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));

    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
}

void Parser::f39() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f40() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(F));
    stack1.push(StackItem(TOKEN_T::MUL_T));

    stack2.push(StackItem(TOKEN_T::MUL_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f41() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(F));
    stack1.push(StackItem(TOKEN_T::DIV_T));

    stack2.push(StackItem(TOKEN_T::DIV_T));
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f42() 
{
    stack1.pop();
    stack1.push(StackItem(V));
    stack1.push(StackItem(TOKEN_T::NAME_T));

    stack2.push(StackItem());
    stack2.push(StackItem(TOKEN_T::NAME_T));
}

void Parser::f43() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::CONST_INT_T));

    stack2.push(StackItem(TOKEN_T::CONST_INT_T));
}

void Parser::f44() 
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::R_PR_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_PR_T));

    stack2.push(StackItem());
    stack2.push(StackItem());
    stack2.push(StackItem());
}

void Parser::f45()
{
    stack1.pop();
    stack1.push(StackItem());

    stack2.push(StackItem("<3>"));
}

void Parser::f46()
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::END_T, STACK_ITEM_T::TERM_T));

    stack2.push(StackItem());
}

void Parser::f47()
{
    stack1.pop();
    stack1.push(StackItem(TOKEN_T::R_SQUARE_T));
    stack1.push(StackItem(E));
    stack1.push(StackItem(TOKEN_T::L_SQUARE_T));

    stack2.push(StackItem("<i>"));
    stack2.push(StackItem());
    stack2.push(StackItem());
}
