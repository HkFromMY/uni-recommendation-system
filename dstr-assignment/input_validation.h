#pragma once
#ifndef input_validation_h

#include <iostream>
#include <regex>
#include <string>
#include <cctype>

using namespace std;

bool validateEmail(string);
bool validatePhone(string);
bool validateRank(string);
bool validateInteger(string);
bool validateDouble(string);

#endif // !input_validation_h
