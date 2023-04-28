#pragma once
#ifndef util_h

#include "LinkedList.h"
#include "University.h"

#include <iostream>
#include <string>

using namespace std;

int convertToInt(string);
double convertToDouble(string);

// file methods
void writeToFile(string, string);
void appendToFile(string, string);

#endif // !util_h
