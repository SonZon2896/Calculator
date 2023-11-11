#include <iostream>
#include <string>
#include "headers/Calculator.h"

/// @brief Input Expression
std::string GetExp()
{
    std::string tempString;
    std::cout << "> ";
    std::getline(std::cin, tempString);
    return tempString;
}

int main()
{
    std::cout << "Chose Mode ('D' - Debug Mode, 'C' - Calculator Mode)\n";
    std::string mode = GetExp();
    if (mode == "C")
        for ( ; true; )
        {
            try
            {
                std::string Input = GetExp();
                if (Input == "q")
                    exit(0);
                else if (Input == "v")
                    PrintVariables();
                else if (Input == "t")
                    PrintTokens();
                else if (Input == "help" || Input == "Help" || Input == "h" || Input == "H")
                    Help();
                else
                {
                    double result = Calculate(Input);
                    std::cout << "= " << result << std::endl;
                }
            }
            catch(const std::runtime_error& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    else if (mode == "D")
        for ( ; true; )
        {
            try
            {
                std::string Input = GetExp();
                if (Input == "q")
                    exit(0);
                else if (Input == "v")
                    PrintVariables();
                else if (Input == "t")
                    PrintTokens();
                else if (Input == "help" || Input == "Help" || Input == "h" || Input == "H")
                    Help();
                else
                {
                    std::string Action;
                    do{
                        std::cout << "Chose action:\n";
                        Action = GetExp();
                        if (Action == "ExpToTokens")
                            ExpToTokens(Input);
                        else if (Action == "PrintTokens")
                            PrintTokens();
                        else if (Action == "PrintVariables")
                            PrintVariables();
                        else if (Action == "Calculate")
                            Calculate(Input);
                        else if (Action == "CalculateWithAOV")
                            CalculateWithAOV(-1, -1);
                    } while (Action != "quit");
                }
            }
            catch(const std::runtime_error& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

    return 0;
}