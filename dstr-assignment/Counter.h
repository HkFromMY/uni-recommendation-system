#pragma once
#ifndef counter_h
#define counter_h

#include <iostream>
#include <string>

using namespace std;

/*
This Counter class is used to encapsulate the key-value pairs of the HashMap that contains the
occurrences of University in users' favourite list
This is used so that the key-value pairs can be sorted according to the value that is integer
*/

class Counter
{
	private:
		string key;
		int value;

	public:
		Counter(string, int);
		~Counter();

		// getters
		string getKey();
		int getValue();

		// setters
		void setKey(string);
		void setValue(int);

		void printDetails();
};

#endif // !counter_h
