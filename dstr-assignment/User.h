#pragma once
#ifndef user_h

#include "Date.h"
#include "LinkedList.h"
#include "Favourite.h"
#include "Feedback.h"

#include <iostream>
#include <string>

using namespace std;

// used for list of constants related to user's roles for better variable management
enum user_role {
	USER = 0,
	GUEST = 1 ,
	ADMIN = 2
};

class User
{
	private:
		int user_id;
		string username; // should be unique
		string password;
		string email;
		string phone;
		Date* last_login_date; // update when registered and login
		string role; // can be user or admin only

		// list objects
		LinkedList<Favourite>* favourite_universities; // saved uni list
		LinkedList<Feedback>* feedback_sent;
		LinkedList<Feedback>* feedback_replies; 

	public:
		User(int, string, string, string, string, string, Date*);
		~User();

		// getters
		int getUserId();
		string getUsername();
		string getPassword();
		string getEmail();
		string getPhone();
		int getRole(); // use to compare with the enum defined above
		Date* getLastLoginDate();

		LinkedList<Favourite>* getFavouriteUniversities();
		LinkedList<Feedback>* getFeedbackSent();
		LinkedList<Feedback>* getFeedbackReplies();

		// setters
		void setUserId(int);
		void setUsername(string);
		void setPassword(string);
		void setEmail(string);
		void setPhone(string);
		void setRole(string);
		void setLastLoginDate(Date*);

		void setFavouriteUniversities(LinkedList<Favourite>*);
		void setFeedbackSent(LinkedList<Feedback>*);
		void setFeedbackReplies(LinkedList<Feedback>*);

		// utility functions
		void printDetails();
		bool isPasswordMatch(string, string);
		bool isInactive();
		string toString(); // return line of string that can be directly written to the file

};

#endif // !user_h

