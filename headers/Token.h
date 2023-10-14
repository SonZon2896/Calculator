#pragma once

#include <string>
#include <iostream>

class Token
{
private:
    char sign;
    double value;
    std::string variable_name;
public:
    Token(char);
    Token(double);
    Token(std::string, double);

    double GetValue();
    char GetSign();
    std::string GetVariable_Name();

    void SetValue(double);

    bool isNumber();
    bool isVariable();

    std::string PrintToken();
    
};

/// @brief Make Token
Token GetToken(char);
Token GetToken(double);
Token GetVariable(std::string, double);