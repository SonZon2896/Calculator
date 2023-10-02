#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <string>

class Token
{
private:
    char sign;
    double value;
public:
    Token(char sign)
    {
        this->sign = sign;
        this->value = 0;
    }
    Token(double value)
    {
        this->sign = '0';
        this->value = value;
    }

    double GetValue() {return this->value;}
    char GetSign() {return this->sign;}

    void SetValue(double value) {this->sign = '0'; this->value = value;}

    bool isNumber() {return this->sign == '0';}

    std::string PrintToken()
    {
        if (this->sign == '0')
            return std::to_string(this->value);
        else
        {
            std::string temp = "";
            temp.push_back(this->sign);
            return temp;
        }
    }
};

/// @brief Make Token by sign or value
Token GetToken(char sign) {return Token(sign);}
Token GetToken(double value) {return Token(value);}

#endif