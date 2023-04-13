#pragma once
#ifndef login_h

#include "LinkedList.h"
#include "User.h"
#include <fstream>

#include <iostream>;

void loginInterface();
User* validateCredentials(string, string);
bool promptLogin();

#endif // !login_h
