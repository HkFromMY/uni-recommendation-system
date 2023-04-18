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
LinkedList<User>* loadUserData(string, bool);

// generate ids for records
int generateUserId();

// file methods
void writeToFile(string, string);
void appendToFile(string, string);

string latestUserRecordInString(LinkedList<User>*);

#endif // !util_h
