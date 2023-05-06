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

void guestInterface();
void displayAllUniversities();
void displayUniRecords(LinkedList<University>*);
void searchUniversityDetails();
void registerAsCustomer();
bool checkRecordUniqueness(string*, string*, string*);

#endif