#include "../headers/Calculator.h"

#define DebugMode

/// @brief Tokens - all Tokens in expression
/// @brief LayersSigns and Signs - Signs, using in Layers
std::vector<Token> Tokens;
std::vector<Token> Variables{Token("pi", 3.14159, true), Token("e", exp(1), true)};
std::string Functions = "sclm";
std::string ThirdLayerSigns = "^!";
std::string SecondLayerSigns = "*/";
std::string FirstLayerSigns = "+-";
const std::string Signs = FirstLayerSigns + SecondLayerSigns + ThirdLayerSigns + "()";

bool In(char ch, std::string signs)
{
    for (int i: signs)
        if (ch == i)
            return true;
    return false;
}

bool In(std::string variable_name, std::vector<Token>& variables)
{
    for (int i = 0; i < variables.size(); i++)
        if (variable_name == variables[i].GetVariable_Name())
            return true;
    return false;
}

void UnpackTemp(std::string& temp)
{
    if (std::isalpha(temp[0]))
        Tokens.push_back(GetVariable(temp, 0.));
    else
    {
        for (int i = 1; i < temp.length(); i++)
        {
            if (isalpha(temp[i]))
                throw std::runtime_error("Not double in temp ExpToTokens(): " + temp);
        }
        Tokens.push_back(GetToken(std::stod(temp)));
    }   
    temp = "";
}

void ExpToTokens(std::string exp)
{
    std::string temp = "";
    for (int i = 0; i < exp.length(); i++)
    {
        //Token "multiply"
        if (i + 7 < exp.length() && temp == "" && exp[i] == 'm' && exp[i+1] == 'u' && exp[i+2] == 'l' && exp[i+3] == 't' && exp[i+4] == 'i' && exp[i+5] == 'p' && exp[i+6] == 'l' && exp[i+7] == 'y')
        {
            if (i + 8 == exp.length() || exp[i+8] == '(' || exp[i+8] == ' ')
                Tokens.push_back('m');
            else
                temp += "multiply";
            i += 7;
            continue;
        }
        //Token "log"
        if (i + 2 < exp.length() && temp == "" && exp[i] == 'l' && exp[i+1] == 'o' && exp[i+2] == 'g')
        {
            if (i + 3 == exp.length() || exp[i+3] == '(' || exp[i+3] == ' ')
                Tokens.push_back('l');
            else
                temp += "log";
            i += 2;
            continue;
        }
        //Token "sin"
        if (i + 2 < exp.length() && temp == "" && exp[i] == 's' && exp[i+1] == 'i' && exp[i+2] == 'n')
        {
            if (i + 3 == exp.length() || exp[i+3] == '(' || exp[i+3] == ' ')
                Tokens.push_back('s');
            else
                temp += "sin";
            i += 2;
            continue;
        }
        //Token "cos"
        if (i + 2 < exp.length() && temp == "" && exp[i] == 'c' && exp[i+1] == 'o' && exp[i+2] == 's')
        {
            if (i + 3 == exp.length() || exp[i+3] == '(' || exp[i+3] == ' ')
                Tokens.push_back('c');
            else
                temp += "cos";
            i+=2;
            continue;
        }
        //Token "const"
        if (i + 4 < exp.length() && temp == "" && exp[i] == 'c' && exp[i+1] == 'o' && exp[i+2] == 'n' && exp[i+3] == 's' && exp[i+4] == 't')
        {
            if (i + 5 == exp.length() || exp[i+5] == ' ')
                Tokens.push_back('C');
            else
                temp += "const";
            i += 4;
            continue;
        }
        //Token "var"
        if (i + 2 < exp.length() && temp == "" && exp[i] == 'v' && exp[i+1] == 'a' && exp[i+2] == 'r')
        {
            if (i + 3 == exp.length() || exp[i+3] == ' ')
                Tokens.push_back('V');
            else
                temp += "var";
            i += 2;
            continue;
        }

        //Token Number or Variable
        if (std::isalpha(exp[i]) || std::isdigit(exp[i]) || exp[i] == '.' || (exp[i] == '-' && isdigit(exp[i+1])))
        {
            temp += exp[i];
            continue;
        }
        //Unpack temp if need
        if (temp != "")
        {
            UnpackTemp(temp);
        }
        //Space
        if (exp[i] == ' ' || exp[i] == ',')
            continue;
        //Token '='
        if (exp[i] == '=')
        {
            if (Tokens.size() > 3)
                throw std::runtime_error("error with '='");
            Tokens.push_back(GetToken(exp[i]));
            continue;
        }

        //Token Sign
        if (In(exp[i], Signs))
            Tokens.push_back(GetToken(exp[i]));
        else
            throw std::runtime_error("Unknown Sign");
    }
    if (temp != "")
    {
        UnpackTemp(temp);
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

void Help()
{
    std::cout << "'q' - quit\n" <<
                 "'v' - Print Variables\n" <<
                 "'t' - Print Tokens\n" <<
                 "Calculator can work with operators: {+, -, *, /, ^, !, ( )}\n" <<
                 "Calculator can work with functions: {sin(), cos(), log(), multiply()}\n";
}

void SetVariable()
{
    //Add const variable
    if (Tokens[0].GetSign() == 'C')
    {
        if (Tokens[1].GetSign() == 'V')
        {
            if (Tokens[2].isVariable() && Tokens[3].GetSign() == '=' && Tokens[4].isNumber())
                if (!In(Tokens[2].GetVariable_Name(), Variables))
                    {
                        Variables.push_back(GetVariable(Tokens[2].GetVariable_Name(), Tokens[4].GetValue(), true));
                        Tokens.erase(Tokens.begin(), Tokens.begin() + 4);
                    }
                else
                    throw std::runtime_error("Declaration of an already declared variable");
            else
                throw std::runtime_error("SetVariable() Error: {" + Tokens[1].PrintToken() + ' ' + Tokens[2].PrintToken() +
                    ' ' + Tokens[3].PrintToken() + Tokens[4].PrintToken() + "};\n Excepted: {var {var_name} = {value}}");
#ifdef DebugMode
            std::cout << "added const variable: {" << Variables[Variables.size() - 1].GetVariable_Name() << "} = {" << Variables[Variables.size() - 1].GetValue() << "}\n";
#endif
        }
    }
    //Add variable
    else if (Tokens[0].GetSign() == 'V')
    {
        if (Tokens[1].GetSign() == 'v' && Tokens[2].GetSign() == '=' && Tokens[3].isNumber())
            if (!In(Tokens[1].GetVariable_Name(), Variables))
                {
                    Variables.push_back(GetVariable(Tokens[1].GetVariable_Name(), Tokens[3].GetValue()));
                    Tokens.erase(Tokens.begin(), Tokens.begin() + 3);
                }
            else
                throw std::runtime_error("Declaration of an already declared variable");
        else
            throw std::runtime_error("SetVariable() Error: {" + Tokens[0].PrintToken() + ' ' + Tokens[1].PrintToken() +
                ' ' + Tokens[2].PrintToken() + Tokens[3].PrintToken() + "};\n Excepted: {var {var_name} = {value}}");
#ifdef DebugMode
        std::cout << "added variable: {" << Variables[Variables.size() - 1].GetVariable_Name() << "} = {" << Variables[Variables.size() - 1].GetValue() << "}\n";
#endif
    }
    //Change variable
    else if (Tokens.size() > 1 && Tokens[1].GetSign() == '=' && Tokens[0].isVariable())
    {
        for (auto& variable: Variables)
            if (variable.GetVariable_Name() == Tokens[0].GetVariable_Name())
            {
                if (variable.isConst())
                    throw std::runtime_error("variable {" + variable.GetVariable_Name() + "} is const");
                variable.ChangeValue(Tokens[2].GetValue());
#ifdef DebugMode
                std::cout << "changed variable: {" << Tokens[0].PrintToken() << "} = {" << Tokens[2].PrintToken() << "}: " << variable.PrintToken() << "\n";
#endif
                Tokens.erase(Tokens.begin(), Tokens.begin() + 2);
                break;
            }
    }
    else 
        for (size_t i = 0; i < 4; ++i)
            if (Tokens[i].GetSign() == '=')
                throw std::runtime_error("error with '='");
}

void DeNameVariable()
{
    for (size_t i = 0; i < Tokens.size(); ++i)
        if (Tokens[i].isVariable() && (i == 0 || Tokens[i-1].GetSign() != 'V') && (i == Tokens.size() - 1 || Tokens[i+1].GetSign() != '='))
            for (size_t j = 0; j < Variables.size(); ++j)
            {
                if (Variables[j].GetVariable_Name() == Tokens[i].GetVariable_Name())
                    {
                        Tokens[i] = GetToken(Variables[j].GetValue());
                        break;
                    }
                else if (j + 1 == Variables.size())
                    throw std::runtime_error("Variable {" + Tokens[i].GetVariable_Name() + "} Not Declare");
            }
}

void Function(const int i)
{
    if (!In(Tokens[i].GetSign(), Functions))
        throw std::runtime_error("Function() Error: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                 + ' ' + Tokens[i+1].PrintToken() + '}');
    
    {
        switch(Tokens[i].GetSign())
        {
            case 's':
                if (!Tokens[i+1].isNumber())
                    throw std::runtime_error("ThirdLayer() Error 3: {" + Tokens[i].PrintToken() + ' ' + Tokens[i+1].PrintToken() + '}');
                Tokens[i].SetValue(sin(Tokens[i+1].GetValue()));
                Tokens.erase(Tokens.begin() + i+1);
                break;
            case 'c':
                if (!Tokens[i+1].isNumber())
                    throw std::runtime_error("ThirdLayer() Error 3: {" + Tokens[i].PrintToken() + ' ' + Tokens[i+1].PrintToken() + '}');
                Tokens[i].SetValue(cos(Tokens[i+1].GetValue()));
                Tokens.erase(Tokens.begin() + i+1);
                break;
            case 'm':
                Tokens.erase(Tokens.begin() + i);
                break;
            case 'l':
                Tokens.erase(Tokens.begin() + i);
                break;
            default:
                throw std::runtime_error("Function() Error 2: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                         + ' ' + Tokens[i+1].PrintToken() + '}');
        }
        return;
    }
}

void ThirdLayer(const int i)
{
    if (!In(Tokens[i].GetSign(), ThirdLayerSigns))
        throw std::runtime_error("ThirdLayer() Error: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                 + ' ' + Tokens[i+1].PrintToken() + '}');
    
    {
        switch(Tokens[i].GetSign())
        {
            case '!':
                if (!(Tokens[i-1].isNumber()))
                    throw std::runtime_error("ThirdLayer() Error 3: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken() + '}');
                Tokens[i].SetValue(tgamma(Tokens[i-1].GetValue() + 1));
                Tokens.erase(Tokens.begin() + i-1);
                break;
            case '^':
                if (!(Tokens[i-1].isNumber() && Tokens[i+1].isNumber()))
                    throw std::runtime_error("ThirdLayer() Error 3: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                             + ' ' + Tokens[i+1].PrintToken() + '}');
                Tokens[i].SetValue(pow(Tokens[i-1].GetValue(), Tokens[i+1].GetValue()));
                Tokens.erase(Tokens.begin() + i+1);
                Tokens.erase(Tokens.begin() + i-1);
                break;
            default:
                throw std::runtime_error("ThirdLayer() Error 2: {" + Tokens[i-1].PrintToken() + ' ' + Tokens[i].PrintToken()
                                         + ' ' + Tokens[i+1].PrintToken() + '}');
        }
        return;
    }
}

void SecondLayer(const int i)
{
    if (!In(Tokens[i].GetSign(), SecondLayerSigns))
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
    if (!In(Tokens[i].GetSign(), FirstLayerSigns))
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
    DeNameVariable();
#ifdef DebugMode
    std::cout << "DeNameVariable() Layer Completed; Result:";
    PrintTokens();
#endif

    if (start > 1 && In(Tokens[start-2].GetSign(), Functions))
    {
        double result = 1;
        switch (Tokens[start-2].GetSign())
        {
            case 'l':
                result = log(Tokens[start+1].GetValue()) / log(Tokens[start].GetValue());
                Tokens[start] = GetToken(result);
                Tokens.erase(Tokens.begin() + start + 1, Tokens.begin() + end+1);
                return;
            case 'm':
                for (size_t i = start; i < end+1; ++i)
                    result *= Tokens[i].GetValue();
                Tokens[start] = GetToken(result);
                Tokens.erase(Tokens.begin() + start+1, Tokens.begin() + end+1);
                return;
            case 's':
                break;
            case 'c':
                break;
            
            default:
                throw std::runtime_error("not function in CalculateExpression: {" + Tokens[start-2].PrintToken() + "}");
        }
    }
    for (int i = start; i < end; i++)
        if (In(Tokens[i].GetSign(), Functions))
        {
            Function(i--);
            end -= 2;
        }
#ifdef DebugMode
    std::cout << "Functions Completed; Result:";
    PrintTokens();
#endif

    for (int i = start; i < end; i++)
        if (In(Tokens[i].GetSign(), ThirdLayerSigns))
        {
            ThirdLayer(i--);
            end -= 2;
        }
#ifdef DebugMode
    std::cout << "ThirdLayer Completed; Result:";
    PrintTokens();
#endif

    for(int i = start; i < end; i++)
        if (In(Tokens[i].GetSign(), SecondLayerSigns))
        {
            SecondLayer(i--);
            end -= 2;
        }
#ifdef DebugMode
    std::cout << "SecondLayer Completed; Result:";
    PrintTokens();
#endif

    for(int i = start; i < end; i++)
        if (In(Tokens[i].GetSign(), FirstLayerSigns))
        {
            FirstLayer(i--);
            end -= 2;
        }
#ifdef DebugMode
    std::cout << "FirstLayer Completed; Result:";
    PrintTokens();
#endif
}

void ErrorHooks()
{
    int Hooks = 0;
    for (int i = 0; i < Tokens.size(); i++)
    {
        Token token = Tokens[i];
        if (token.GetSign() == '(') 
        {
            Hooks++;
        }
        else if (token.GetSign() == ')') Hooks--;
        if (Hooks < 0) 
            throw std::runtime_error("Hooks error ')': {" + std::to_string(i + 1) + "}");
    }
    if (Hooks != 0)
        throw std::runtime_error("Hooks error '('");
}

void CalculateWithAOV(int start, int end)
{
    if (start == -1)
    {
        ErrorHooks();
        start = 0;
        end = Tokens.size();
    }
    for (int i = start; i < end; i++)
    {
        if (Tokens[i].GetSign() == '(')
        {
            int hooks = 0;
            for (int j = i + 1; j < Tokens.size(); j++)
            {
                if (Tokens[j].GetSign() == '(')
                    hooks++;
                else if (Tokens[j].GetSign() == ')' && hooks != 0)
                    hooks--;
                else if (Tokens[j].GetSign() == ')' && hooks == 0)
                {
                    int prevTokensSize = Tokens.size();
                    CalculateWithAOV(i+1, j-1);
                    Tokens.erase(Tokens.begin() + i + 2);
                    Tokens.erase(Tokens.begin() + i);
#ifdef DebugMode
                    std::cout << "Calculate Expression ended, Tokens:";
                    PrintTokens();
#endif
                    end = end - (prevTokensSize - Tokens.size());
                    break;
                }
            }
        }
    }
    CalculateExpression(start, end);
#ifdef DebugMode
    std::cout << "Calculate Ended, Tokens:";
    PrintTokens();
#endif
}

double Calculate(std::string expression)
{
    Tokens.clear();
    ExpToTokens(expression);
#ifdef DebugMode
    std::cout << "ExpToTokens() completed; Tokens:";
    PrintTokens();
#endif
    CalculateWithAOV(-1, -1);
    SetVariable();
    return Tokens[0].GetValue();
}
