#pragma once
#ifndef feedback_model_h
#define feedback_model_h

#include <iostream>
#include <string>
#include "util.h"

#include "LinkedList.h"
#include "Node.h"
#include "Feedback.h"

using namespace std;

// implemented using merge sort
Node<Feedback>* sortFeedbackByDate(Node<Feedback>*);
Node<Feedback>* mergeFeedback(Node<Feedback>*, Node<Feedback>*);
Node<Feedback>* splitFeedback(Node<Feedback>*);

// search & filter
LinkedList<Feedback>* filterFeedbacksByType(LinkedList<Feedback>*, string);

LinkedList<Feedback>* loadFeedbackData(string);
int generateFeedbackId();
void appendNewFeedbackOnFile(Feedback*);
string latestFeedbackRecordInString(LinkedList<Feedback>*);

#endif // !feedback_model_h
