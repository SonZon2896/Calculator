#pragma once

#include <string>
#include <iostream>

class Token
{
private:
    char sign;
    double value;
    std::string variable_name;
    bool is_const;
public:
    Token(char);
    Token(double);
    Token(std::string, double, bool);

    double GetValue();
    char GetSign();
    std::string GetVariable_Name();

    void SetValue(double);
    void ChangeValue(double);

    bool isNumber();
    bool isVariable();
    bool isConst();

    std::string PrintToken();
    
};

/// @brief Make Token
Token GetToken(char);
Token GetToken(double);
Token GetVariable(std::string, double, bool = false);