#include "../headers/Calculator.h"

bool CharInSigns(char ch, std::string signs)
{
    for (int i: signs)
        if (ch == i)
            return true;
    return false;
}

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

void PrintTokens()
{
    std::cout << "\n====TOKENS====\n";
    for (auto i: Tokens)
        std::cout << i.PrintToken() << ' ';
    std::cout << "\n====TOKENS====\n";
}

void PrintError(std::string message)
{
    std::cout << "ERROR:\n" << message;
    exit(0);
}

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

void CalculateWithAOV(int start, int end)
{
    if (start == -1)
        start = 0;
    if (end == -1)
        end = Tokens.size();
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
    CalculateWithAOV(-1, -1);
    return Tokens[0].GetValue();
}