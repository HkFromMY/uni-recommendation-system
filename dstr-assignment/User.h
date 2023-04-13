#pragma once
#ifndef user_h

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
		string username;
		string password;
		string role; // can be user or admin only

	public:
		User(string, string, string);
		~User();

		// getters
		string getUsername();
		string getPassword();
		string getRole();

		// setters
		void setUsername(string);
		void setPassword(string);
		void setRole(string);

		// print details
		void printDetails();
		bool isPasswordMatch(string, string);

};

#endif // !user_h

