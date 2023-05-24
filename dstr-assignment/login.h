#pragma once
#ifndef login_h

#include "LinkedList.h"
#include "User.h"
#include <fstream>

#include <iostream>;

void loginInterface(LinkedList<User>*, LinkedList<University>*, LinkedList<Feedback>*, LinkedList<Favourite>*);
User* validateCredentials(LinkedList<User>*, string, string);
bool promptLogin();

#endif // !login_h
