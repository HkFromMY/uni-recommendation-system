#pragma once
#ifndef university_model_h
#define university_model_h

#include <iostream>
#include <string>

#include "LinkedList.h"
#include "Node.h"
#include "University.h"
#include "util.h"

using namespace std;

// can add trim string functions here
LinkedList<University>* loadUniversitiesData(string);

#endif // !university_model_h
