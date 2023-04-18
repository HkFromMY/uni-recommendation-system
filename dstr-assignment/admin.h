#pragma once
#ifndef admin_h

#include "User.h"
#include "LinkedList.h"

#include <iostream>
#include <string>

using namespace std;

void adminInterface();
void displayRegisteredUserDetails();
bool promptUserAction(User*, string);
string latestUserRecordInString(LinkedList<User>*);

// functions to manipulate user file
void editUserOnFile(int, string, string, string, string);
void deleteUserOnFile(int);

void displayInactiveUser();
void displayFeedbacks();
void displayUniversities();

#endif // !admin_h
