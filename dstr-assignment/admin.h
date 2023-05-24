#pragma once
#ifndef admin_h

#include "User.h"
#include "LinkedList.h"
#include "Counter.h"

#include "common_interface.h"
#include "input_validation.h"
#include "user_model.h"
#include "university_model.h"
#include "feedback_model.h"
#include "favourite_model.h"

#include <iostream>
#include <string>

using namespace std;

void adminInterface(User*, LinkedList<User>*, LinkedList<University>*, LinkedList<Feedback>*, LinkedList<Favourite>*);
void displayRegisteredUserDetails(LinkedList<User>*);
void editUser(User*, LinkedList<User>*);
void deleteUserAccount(User*, LinkedList<User>*);
bool promptUserAction(User*, string);

void displayInactiveUser(LinkedList<User>*);
void displayFeedbacks(User*, LinkedList<Feedback>*);
void sendFeedbackReply(User*, LinkedList<Feedback>*, int);
void displayUniversities(LinkedList<University>*, LinkedList<Favourite>*);

#endif // !admin_h
