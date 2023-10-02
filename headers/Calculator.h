#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Token.h"

/// @brief Tokens - all Tokens in expression
/// @brief LayersSigns and Signs - Signs, using in Layers
std::vector<Token> Tokens;
std::string ThirdLayerSigns = "^";
std::string SecondLayerSigns = "*/";
std::string FirstLayerSigns = "+-";
const std::string Signs = FirstLayerSigns + SecondLayerSigns + ThirdLayerSigns + "()";


bool CharInSigns(char ch, std::string signs)
{
    for (int i: signs)
        if (ch == i)
            return true;
    return false;
}

/// @brief Convert Expression To Tokens
void ExpToTokens(std::string exp)
{
    std::string strValue = "";
    for (int i = 0; i < exp.length(); i++)
    {
        if (exp[i] == ' ')
            continue;
        if ((int('0') <= int(exp[i]) && int(exp[i]) <= int('9')) || exp[i] == '.')
        {
            strValue += exp[i];
            continue;
        }
        if (strValue != "")
        {
            Tokens.push_back(GetToken(std::stod(strValue)));
            strValue = "";
        }
        bool isSign = CharInSigns(exp[i], Signs);
        if (isSign)
            Tokens.push_back(GetToken(exp[i]));
        else
        {
            std::cerr << exp[i] << " - CHTO ETO?????";
            exit(0);
        }        
    }
    if (strValue != "")
            Tokens.push_back(GetToken(std::stod(strValue)));
}

/// @brief Output Tokens (Debug)
void PrintTokens()
{
    std::cout << "\n====TOKENS====\n";
    for (auto i: Tokens)
        std::cout << i.PrintToken() << ' ';
    std::cout << "\n====TOKENS====\n";
}


/// @brief Exit Program with Error "message"
void PrintError(std::string message)
{
    std::cout << "ERROR:\n" << message;
    exit(0);
}

/// @brief Layers by importance (the more the faster)
void ThirdLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), ThirdLayerSigns))
        PrintError("ThirdLayer() Error");
    if (Tokens[i-1].isNumber() && Tokens[i+1].isNumber())
    {
        switch(Tokens[i].GetSign())
        {
            case '^':
                Tokens[i].SetValue(pow(Tokens[i-1].GetValue(), Tokens[i+1].GetValue()));
                break;
            default:
                PrintError("ThirdLayer() Error 2");
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    PrintError("ThirdLayer() Error 3");
}

void SecondLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), SecondLayerSigns))
        PrintError("SecondLayer() Error");
    if (Tokens[i-1].isNumber() && Tokens[i+1].isNumber())
    {
        switch(Tokens[i].GetSign())
        {
            case '*':
                Tokens[i].SetValue(Tokens[i-1].GetValue() * Tokens[i+1].GetValue());
                break;
            case '/':
                Tokens[i].SetValue(Tokens[i-1].GetValue() / Tokens[i+1].GetValue());
                break;
            default:
                PrintError("SecondLayer() Error 2");
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    PrintError("SecondLayer() Error 3");
}

void FirstLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), FirstLayerSigns))
        PrintError("FirstLayer() Error");
    if (Tokens[i-1].isNumber() && Tokens[i+1].isNumber())
    {
        switch(Tokens[i].GetSign())
        {
            case '+':
                Tokens[i].SetValue(Tokens[i-1].GetValue() + Tokens[i+1].GetValue());
                break;
            case '-':
                Tokens[i].SetValue(Tokens[i-1].GetValue() - Tokens[i+1].GetValue());
                break;
            default:
                PrintError("FirstLayer() Error 2");
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    PrintError("FirstLayer() Error 3");
}

/// @brief calculate expression in area of visibility by '(' and ')'
void CalculateExpression(const int start, int end)
{
    //PrintTokens();
    for (int i = start + 1; i < end; i++)
        if (CharInSigns(Tokens[i].GetSign(), ThirdLayerSigns))
        {
            ThirdLayer(i--);
            end -= 2;
        }
    //PrintTokens();
    for(int i = start + 1; i < end; i++)
        if (CharInSigns(Tokens[i].GetSign(), SecondLayerSigns))
        {
            SecondLayer(i--);
            end -= 2;
        }
    //PrintTokens();
    for(int i = start + 1; i < end; i++)
        if (CharInSigns(Tokens[i].GetSign(), FirstLayerSigns))
        {
            FirstLayer(i--);
            end -= 2;
        }
    //PrintTokens();
}

/// @brief main function, find minimal area of visibility and start CalculateExpression()
void CalculateWithAOV(const int start = 0, int end = Tokens.size())
{
    for (int i = start; i < end; i++)
    {
        if (Tokens[i].GetSign() == '(')
        {
            int skob = 0;
            for (int j = i + 1; j < Tokens.size(); j++)
            {
                if (Tokens[j].GetSign() == '(')
                    skob++;
                else if (Tokens[j].GetSign() == ')' && skob != 0)
                    skob--;
                else if (Tokens[j].GetSign() == ')' && skob == 0)
                {
                    //std::cout << "Enter in ()\n";
                    int prevTokensSize = Tokens.size();
                    CalculateWithAOV(i+1, j-1);
                    Tokens.erase(Tokens.begin() + i + 2);
                    Tokens.erase(Tokens.begin() + i);
                    //std::cout << "Colculate Expression enden, Tokens:";
                    //PrintTokens();
                    end = end - (prevTokensSize - Tokens.size());
                    break;
                }
            }
        }
    }
    CalculateExpression(start, end);
    //std::cout << "Colculate Ended, Tokens:";
    //PrintTokens();
}

double Calculate(std::string expression)
{
    ExpToTokens(expression);
    CalculateWithAOV();
    return Tokens[0].GetValue();
}

#endif