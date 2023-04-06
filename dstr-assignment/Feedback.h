#pragma once
#ifndef feedback_h
#define feedback_h

#include <iostream>
#include <string>

using namespace std;

class Feedback
{
	private:
		string sender_id;
		string comment;

	public:
		Feedback(string, string);
		~Feedback();
		string getSenderId();
		string getComment();

		void setSenderId(string);
		void setComment(string);

		void printDetails();

};

#endif // DEBUG
