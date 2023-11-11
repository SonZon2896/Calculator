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
Token::Token(std::string variable_name, double value, bool is_const)
{
    this->sign = 'v';
    this->value = value;
    this->variable_name = variable_name;
    this->is_const = is_const;
}

double Token::GetValue() {return this->value;}
char Token::GetSign() {return this->sign;}
std::string Token::GetVariable_Name() {return this->variable_name;}

void Token::SetValue(double value) 
{
    this->sign = '0'; 
    this->value = value;
}

void Token::ChangeValue(double value)
{
    this->value = value;
}

bool Token::isNumber() 
{
    return sign == '0';
}
bool Token::isVariable()
{
    return this->sign == 'v';
}
bool Token::isConst()
{
    return this->is_const;
}

std::string Token::PrintToken()
{
    if (sign == '0')
        return std::to_string(value);
    if (sign == 'v')
        return (is_const ? "const_" : "") + variable_name + '(' + std::to_string(value) + ')';
    else
    {
        std::string temp = "";
        temp.push_back(sign);
        return temp;
    }
}

Token GetToken(char sign) {return Token(sign);}
Token GetToken(double value) {return Token(value);}
Token GetVariable(std::string variable_name, double value, bool is_const) {return Token(variable_name, value, is_const);}