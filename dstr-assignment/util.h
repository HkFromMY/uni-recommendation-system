#pragma once
#ifndef util_h

#include "LinkedList.h"
#include "University.h"

#include <iostream>
#include <string>

using namespace std;

int convertToInt(string);
double convertToDouble(string);

LinkedList<University>* loadCSVFile(string);

#endif // !util_h
