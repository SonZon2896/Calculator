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
    for ( ; true; )
    {
        try
        {
            std::string Input = GetExp();
            if (Input == "q")
                exit(0);
            else if (Input == "v")
                PrintVariables();
            else
                std::cout << "= " << Calculate(Input) << std::endl;
        }
        catch(const std::runtime_error& e)
        {
            std::cerr << e.what() << '\n';
        }
    }

    return 0;
}