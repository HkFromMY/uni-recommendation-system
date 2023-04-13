#pragma once
#ifndef util_h

#include "LinkedList.h"
#include "University.h"
#include "User.h"

#include <iostream>
#include <string>

using namespace std;

int convertToInt(string);
double convertToDouble(string);
// can add trim string functions here
LinkedList<University>* loadCSVFile(string);
LinkedList<User>* loadUserData(string);

#endif // !util_h
