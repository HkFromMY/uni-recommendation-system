#pragma once
#ifndef favourite_h
#define favourite_h

#include <iostream>
#include <string>

using namespace std;

class Favourite
{
	private:
		int favourite_id;
		int user_id; // favourite that belongs to which users
		string favourite_university;

	public:
		Favourite(int, int, string);
		~Favourite();

		// getters
		int getFavouriteId();
		int getUserId();
		string getFavouriteUniversity();

		// setters
		void setFavouriteId(int);
		void setUserId(int);
		void setFavouriteUniversity(string);

		// utility function
		void printDetails();
		string toString();
};

#endif // !favourite_h
