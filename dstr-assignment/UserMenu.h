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

void userInterface(User*, LinkedList<User>*, LinkedList<University>*, LinkedList<Feedback>*, LinkedList<Favourite>*);
void displayUniversityDetails(User*, LinkedList<University>*, LinkedList<Favourite>*);
void displayUniversityRecords(User*, LinkedList<University>*, LinkedList<Favourite>*);
void searchUniversityMenu(User*, LinkedList<University>*, LinkedList<Favourite>*);
int promptAction(User*, Node<University>*, LinkedList<Favourite>*);

// favourite modules
void saveUniversityAsFavourite(User*, Favourite*, LinkedList<Favourite>*);
void displaySavedUniversities(User*, LinkedList<Favourite>*);
void deleteFavouriteUniversity(User*, LinkedList<Favourite>*);

// feedback module
void displayFeedback(User*, LinkedList<User>*, LinkedList<Feedback>*);
void sendFeedback(User*, LinkedList<User>*, LinkedList<Feedback>*);
void displayFeedbackReplies(User*);

// edit user profile
void editUserProfile(User*, LinkedList<User>*);
