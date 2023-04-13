#pragma once
#ifndef login_h

#include "LinkedList.h"
#include "User.h"
#include <fstream>

#include <iostream>;

void loginInterface();
bool validateCredentials(string, string);
LinkedList<User>* loadUserData(string);
bool promptLogin();

#endif // !login_h
