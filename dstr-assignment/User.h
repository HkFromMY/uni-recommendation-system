#pragma once
#ifndef user_h

#include <iostream>
#include <string>

using namespace std;

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

