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
LinkedList<University>* loadUniversitiesData();

// merge sort for universities
Node<University>* sortUniversities(Node<University>*, string*, string*, bool);
Node<University>* splitUniversities(Node<University>*);
Node<University>* mergeUniversities(Node<University>*, Node<University>*, string*, string*, bool);
bool compareValue(University*, University*, string*, string*, bool);
#endif // !university_model_h
