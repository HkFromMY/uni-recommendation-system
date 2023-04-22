#pragma once
#ifndef feedback_h
#define feedback_h

#include <iostream>
#include <string>
#include "Date.h"

using namespace std;

class Feedback
{
	private:
		int feedback_id;
		int sender_id; // user_id on user.txt
		int recipient_id; // user_id on user.txt (usually admin)
		string comment;
		Date* send_date;

	public:
		Feedback(int, int, int, string); // for creating a new feedback
		Feedback(int, int, int, string, Date*); // for loading an existing feedback
		~Feedback();

		// getters
		int getFeedbackId();
		int getSenderId();
		int getRecipientId();
		string getComment();
		Date* getSendDate();

		// setters
		void setFeedbackId(int);
		void setSenderId(int);
		void setRecipientId(int);
		void setComment(string);
		void setSendDate(Date*);

		// utility
		void printDetails();

};

#endif // DEBUG
