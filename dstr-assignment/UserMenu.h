#pragma once
#include "User.h"
#include "LinkedList.h"
#include "University.h"
#include "util.h"
#include "common_interface.h"
#include "search.h"
#include "input_validation.h"
#include "login.h"
#include "university_model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void userInterface(User*);
void displayUniversityDetails();
void displayUniversityRecords(LinkedList<University>*);
bool promptUserAction(User*, string);
void searchUniversity();
void sortOptions();
void displaySavedUniversities();
void displayFeedback();
void displayFeedbackReplies();