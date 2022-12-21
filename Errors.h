#pragma once

#include <stdexcept>
#include <exception>
#include <string>
#include <iostream>
#include "RPN.h"
#include "Token.h"

class SyntaxError : public std::runtime_error 
{
public:
    SyntaxError(Token t)
        : std::runtime_error("Syntax Error! <" + t.word() + "> (" + std::to_string(t.row) + " , " + std::to_string(t.col) + ")") {};
};

class IllegalCharacter : public std::runtime_error 
{
public:
    IllegalCharacter(Token t)
        : std::runtime_error("Illegal character! : " + t.word()) {};
};

class RuntimeError : public std::runtime_error 
{
public:
    RuntimeError(std::string word)
        : std::runtime_error("Runtime error ! : " + word) {}
};

class DeclarationError : public std::runtime_error 
{
public:
    DeclarationError(Token t)
        : std::runtime_error("Declaration Error! : " + t.word()) {};
};

class InitializationError : public std::runtime_error 
{
public:
    explicit InitializationError(RPSItem i)
        : std::runtime_error("Initialization error ! : " + i.word + " wasn't declared!")  {};
};

