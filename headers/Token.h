#pragma once

#include <string>
#include <iostream>

class Token
{
private:
    char sign;
    double value;
public:
    Token(char sign);
    Token(double value);

    double GetValue() {return this->value;}
    char GetSign() {return this->sign;}

    void SetValue(double value);

    bool isNumber();

    std::string PrintToken();
    
};

/// @brief Make Token by sign or value
Token GetToken(char sign);
Token GetToken(double value);