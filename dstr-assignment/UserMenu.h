#pragma once
#include "User.h"
#include "LinkedList.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void userInterface();
void displayUniversityDetails();
bool promptUserAction(User*, string);
void searchUniversity();
void sortOptions();
void displaySavedUniversities();
void displayFeedback();
void displayFeedbackReplies();