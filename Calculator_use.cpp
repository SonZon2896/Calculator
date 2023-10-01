#include <iostream>
#include <string>
#include "Calculator.h"

/// @brief Input Expression
std::string GetExp()
{
    std::string tempString;
    std::getline(std::cin, tempString);
    return tempString;
}

int main()
{
    std::cout << "input expression: ";
    std::string Input = GetExp();
    std::cout << "result: " << Calculate(Input) << std::endl;

    return 0;
}