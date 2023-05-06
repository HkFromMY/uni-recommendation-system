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
#include "Favourite.h"
#include "Feedback.h"
#include "favourite_model.h"
#include "user_model.h"
#include "feedback_model.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

void userInterface(User*);
void displayUniversityDetails(User*);
void displayUniversityRecords(User*, LinkedList<University>*);
void searchUniversityMenu(User*);
void saveUniversityAsFavourite(User*, Favourite*);
void displaySavedUniversities(User*);
void displayFeedback(User*);
void sendFeedback(User*);
void displayFeedbackReplies(User*);
