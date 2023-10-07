#include "../headers/Token.h"

Token::Token(char sign)
{
    this->sign = sign;
    this->value = 0;
}

Token::Token(double value)
{
    this->sign = '0';
    this->value = value;
}

void Token::SetValue(double value) 
{
    this->sign = '0'; 
    this->value = value;
}

bool Token::isNumber() 
{
    return sign == '0';
}

std::string Token::PrintToken()
{
    if (sign == '0')
        return std::to_string(value);
    else
    {
        std::string temp = "";
        temp.push_back(sign);
        return temp;
    }
}

Token GetToken(char sign) {return Token(sign);}
Token GetToken(double value) {return Token(value);}