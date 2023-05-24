#pragma once
#ifndef guest_h

#include "LinkedList.h"
#include "University.h"
#include "User.h"

#include "common_interface.h"
#include "university_model.h"
#include "input_validation.h"
#include "user_model.h"

#include <iostream>

using namespace std;

void guestInterface(LinkedList<User>*, LinkedList<University>*);
void displayAllUniversities(LinkedList<University>*);
void displayUniRecords(LinkedList<University>*);
void searchUniversityDetails(LinkedList<University>*);
bool promptReSearch(Node<University>*);
void registerAsCustomer(LinkedList<User>*);
bool checkRecordUniqueness(string*, string*, string*);

#endif