#include "../headers/Calculator.h"

/// @brief Tokens - all Tokens in expression
/// @brief LayersSigns and Signs - Signs, using in Layers
std::vector<Token> Tokens;
std::vector<Token> Variables;
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

bool VarInVariables(std::string variable_name)
{
    for (int i = 0; i < Variables.size(); i++)
        if (variable_name == Variables[i].GetVariable_Name())
            return true;
    return false;
}

void ExpToTokens(std::string exp)
{
    std::string temp = "";
    for (int i = 0; i < exp.length(); i++)
    {
        if (i + 2 < exp.length() && temp == "" && exp[i] == 'v' && exp[i+1] == 'a' && exp[i+2] == 'r')
        {
            if (exp[i+3] == ' ' && i == 0)
            {
                Tokens.push_back('V');
                i += 2;
                continue;
            }
            throw std::runtime_error("'var' out of place");
        }
        if (std::isalpha(exp[i]) || std::isdigit(exp[i]) || exp[i] == '.')
        {
            temp += exp[i];
            continue;
        }
        if (temp != "")
        {
            //std::cout << "temp {" << temp << "}" << std::endl;
            if (std::isalpha(temp[0]))
                Tokens.push_back(GetVariable(temp, 0.));
            else
            {
                try
                {
                    Tokens.push_back(GetToken(std::stod(temp)));
                }
                catch(const std::invalid_argument& e)
                {
                    throw std::runtime_error("Not double in temp ExpToTokens(): " + temp);
                }
            }   
            temp = "";
        }
        if (exp[i] == ' ')
            continue;
        if (exp[i] == '=')
        {
            if (Tokens.size() == 2 && Tokens[0].GetSign() == 'V')
                Tokens.push_back(GetToken(exp[i]));
            else
                throw std::runtime_error("'=' out of place");
            continue;
        }

        if (CharInSigns(exp[i], Signs))
            Tokens.push_back(GetToken(exp[i]));
        else
            throw std::runtime_error("Unknown Sign");
    }
    if (temp != "")
    {
        //std::cout << "temp {" << temp << "}" << std::endl;
        if (std::isalpha(temp[0]))
            Tokens.push_back(GetVariable(temp, 0.));
        else
        {
            try
            {
                Tokens.push_back(GetToken(std::stod(temp)));
            }
            catch(const std::invalid_argument& e)
            {
                throw std::runtime_error("Not double in temp ExpToTokens(): " + temp);
            }
        }   
        temp = "";
    }
}

void PrintTokens()
{
    std::cout << "\n====TOKENS====\n";
    for (auto i: Tokens)
        std::cout << i.PrintToken() << ' ';
    std::cout << "\n====TOKENS====\n";
}

void PrintVariables()
{
    std::cout << "\n====VARIABLES====\n";
    for (auto i: Variables)
        std::cout << i.PrintToken() << ' ';
    std::cout << "\n====VARIABLES====\n";
}

void SetVariable()
{
    if (Tokens[0].GetSign() == 'V')
    {
        if (Tokens[1].GetSign() == 'v' && Tokens[2].GetSign() == '=' && Tokens[3].isNumber())
            if (!VarInVariables(Tokens[1].GetVariable_Name()))
                {
                    Variables.push_back(GetVariable(Tokens[1].GetVariable_Name(), Tokens[3].GetValue()));
                    Tokens.erase(Tokens.begin(), Tokens.begin() + 3);
                }
            else
                throw std::runtime_error("Declaration of an already declared variable");
        else
            throw std::runtime_error("SetVariable() Error: {" + Tokens[0].PrintToken() + ' ' + Tokens[1].PrintToken() +
                ' ' + Tokens[2].PrintToken() + Tokens[3].PrintToken() + "};\n Excepted: {var {var_name} = {value}}");
    }
}

void DeNameVariable(const int i)
{
    for (int j = 0; j < Variables.size(); j++)
        if (Variables[j].GetVariable_Name() == Tokens[i].GetVariable_Name())
            {
                Tokens[i] = GetToken(Variables[j].GetValue());
                return;
            }
    throw std::runtime_error("Variable {" + Tokens[i].GetVariable_Name() + "} Not Declare");
}

void ThirdLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), ThirdLayerSigns))
        throw std::runtime_error("ThirdLayer() Error: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                 + ' ' + Tokens[i+1].PrintToken() + '}');
    if (Tokens[i-1].isNumber() && Tokens[i+1].isNumber())
    {
        switch(Tokens[i].GetSign())
        {
            case '^':
                Tokens[i].SetValue(pow(Tokens[i-1].GetValue(), Tokens[i+1].GetValue()));
                break;
            default:
                throw std::runtime_error("ThirdLayer() Error 2: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                         + ' ' + Tokens[i+1].PrintToken() + '}');
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    throw std::runtime_error("ThirdLayer() Error 3: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                             + ' ' + Tokens[i+1].PrintToken() + '}');
}

void SecondLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), SecondLayerSigns))
        throw std::runtime_error("SecondLayer() Error: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                 + ' ' + Tokens[i+1].PrintToken() + '}');
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
                throw std::runtime_error("SecondLayer() Error 2: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                         + ' ' + Tokens[i+1].PrintToken() + '}');
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    throw std::runtime_error("SecondLayer() Error 3: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                             + ' ' + Tokens[i+1].PrintToken() + '}');
}

void FirstLayer(const int i)
{
    if (!CharInSigns(Tokens[i].GetSign(), FirstLayerSigns))
        throw std::runtime_error("FirstLayer() Error: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                 + ' ' + Tokens[i+1].PrintToken() + '}');
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
                throw std::runtime_error("FirstLayer() Error 2: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                         + ' ' + Tokens[i+1].PrintToken() + '}');
        }
        Tokens.erase(Tokens.begin() + i+1);
        Tokens.erase(Tokens.begin() + i-1);
        return;
    }
    throw std::runtime_error("FirstLayer() Error 3: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                             + ' ' + Tokens[i+1].PrintToken() + '}');
}

void CalculateExpression(const int start, int end)
{
    //PrintTokens();
    for (int i = start; i < end; i++)
        if (Tokens[i].isVariable() && !(Tokens[0].GetSign() == 'V' && i == 1))
            DeNameVariable(i);
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
    Tokens.clear();
    ExpToTokens(expression);
    CalculateWithAOV(-1, -1);
    SetVariable();
    //PrintVariables();
    //PrintTokens();
    return Tokens[0].GetValue();
}