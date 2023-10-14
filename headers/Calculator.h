#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Token.h"

bool CharInSigns(char ch, std::string signs);

bool VarInVariables(std::string variable_name);

/// @brief seek variable
/// @param variable_name 
/// @return value in Variables by variable_name
double DeNameVariable(std::string variable_name);

/// @brief Convert Expression To Tokens
/// @param exp expression
void ExpToTokens(std::string exp);

/// @brief Output Tokens (Debug)
void PrintTokens();

/// @brief Output Variables (Debug)
void PrintVariables();

/// @brief set variable = value
void SetVariables();

/// @brief Layers by importance (then more then faster)
void DeNameVariable(const int i);

void ThirdLayer(const int i);

void SecondLayer(const int i);

void FirstLayer(const int i);

/// @brief calculate expression in area of visibility by '(' and ')'
void CalculateExpression(const int start, int end);

/// @brief main function on exp, find minimal area of visibility and start CalculateExpression()
void CalculateWithAOV(const int start, int end);

/// @brief main function
/// @param expression 
/// @return result of expression
double Calculate(std::string expression);