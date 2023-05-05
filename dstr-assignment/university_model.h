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

// binary search for universities
Node<University>* searchUniversityByText(Node<University>*, string*, string*);
Node<University>* searchUniversityByScore(Node<University>*, string*, double);
Node<University>* searchUniversityByRank(Node<University>*, string*, int);
Node<University>* searchUniversityByRankObj(Node<University>*, string*, Rank*);
Node<University>* findMiddleUniversityNode(Node<University>*, Node<University>*);

bool compareUniversityValue(University*, University*, string*, string*, bool);
#endif // !university_model_h
