#pragma once
#ifndef Date_h
#define Date_h

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

using namespace std;

bool isLeapYear(int); // helper function to check whether the year is a leap year
bool isValidDate(int, int, int); // helper function to validate date

class Date
{
	private:
		int year;
		int month;
		int day;

	public:
		Date(); // set current date if default constructor is called
		Date(int, int, int); // construct date object from integers
		Date(string); // directly accept string and convert to date
		~Date();

		// getters
		int getYear();
		int getMonth();
		int getDay();

		// setters
		void setYear(int);
		void setMonth(int);
		void setDay(int);

		// print date object in string format
		void printDate();
		string toString();

		// for comparing dates
		bool isAfter(Date*); 
		bool isBefore(Date*);
		bool isEqual(Date*);

		// calculate differences between date
		int differenceBetweenTwoDates(Date*); // return days
};

#endif
