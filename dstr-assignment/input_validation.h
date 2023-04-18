#pragma once
#ifndef input_validation_h

#include <iostream>
#include <regex>
#include <string>
#include <cctype>

using namespace std;

bool validateEmail(string email);
bool validatePhone(string phone);

#endif // !input_validation_h
