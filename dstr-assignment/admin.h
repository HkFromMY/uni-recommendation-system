#pragma once
#ifndef admin_h

#include "User.h"
#include "LinkedList.h"
#include "Counter.h"

#include "common_interface.h"
#include "input_validation.h"
#include "user_model.h"
#include "feedback_model.h"
#include "favourite_model.h"

#include <iostream>
#include <string>

using namespace std;

void adminInterface(User*);
void displayRegisteredUserDetails();
bool promptUserAction(User*, string);
string latestUserRecordInString(LinkedList<User>*);

// functions to manipulate user file
void editUserOnFile(int, string, string, string, string);
void deleteUserOnFile(int);

void displayInactiveUser();
void displayFeedbacks(User*);
void displayUniversities();

#endif // !admin_h
