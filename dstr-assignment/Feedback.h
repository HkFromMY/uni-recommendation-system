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
		string sender_id;
		string comment;
		Date* send_date;

	public:
		Feedback(string, string);
		~Feedback();

		// getters
		string getSenderId();
		string getComment();
		Date* getSendDate();

		// setters
		void setSenderId(string);
		void setComment(string);
		void setSendDate(Date*);

		// utility
		void printDetails();

};

#endif // DEBUG
