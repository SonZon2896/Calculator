#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Token.h"


bool CharInSigns(char ch, std::string signs);

/// @brief Convert Expression To Tokens
void ExpToTokens(std::string exp);

/// @brief Output Tokens (Debug)
void PrintTokens();


/// @brief Exit Program with Error "message"
void PrintError(std::string message);

/// @brief Layers by importance (the more the faster)
void ThirdLayer(const int i);

void SecondLayer(const int i);

void FirstLayer(const int i);

/// @brief calculate expression in area of visibility by '(' and ')'
void CalculateExpression(const int start, int end);

/// @brief main function, find minimal area of visibility and start CalculateExpression()
void CalculateWithAOV(const int start, int end);

double Calculate(std::string expression);