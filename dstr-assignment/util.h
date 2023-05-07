#pragma once
#ifndef util_h

#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

int convertToInt(string);
double convertToDouble(string);
string trimString(string);

// file methods
void writeToFile(string, string);
void appendToFile(string, string);

#endif // !util_h
