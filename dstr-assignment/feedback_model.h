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
Node<Feedback>* sortFeedbackByDate(Node<Feedback>*, bool);
Node<Feedback>* mergeFeedback(Node<Feedback>*, Node<Feedback>*, bool);
Node<Feedback>* splitFeedback(Node<Feedback>*);
bool compareSendDateResult(Feedback*, Feedback*, bool);

// search & filter
LinkedList<Feedback>* filterFeedbacksByType(LinkedList<Feedback>*, string);
LinkedList<Feedback>* filterFeedbacksBySenderId(LinkedList<Feedback>*, int);
LinkedList<Feedback>* filterFeedbacksByRecipientId(LinkedList<Feedback>*, int);

LinkedList<Feedback>* loadFeedbackData();
int generateFeedbackId(LinkedList<Feedback>*);
string latestFeedbackRecordInString(LinkedList<Feedback>*);
void updateLatestFeedbacksOnTextFile(LinkedList<Feedback>*);

#endif // !feedback_model_h
