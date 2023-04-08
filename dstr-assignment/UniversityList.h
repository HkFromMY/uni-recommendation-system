#pragma once
#ifndef Linkedlist_h
#define Linkedlist_h

#include "UniversityNode.h";
#include "University.h"
#include <string>
#include <iostream>
#include <fstream>

class UniversityList
{
	// a doubly circular linked list that can traverse in two direction and
	// 1. from last element to first element
	// 2. from first element to last element

	private:
		UniversityNode* head;
		UniversityNode* last;
		int count;

	public:
		UniversityList();
		~UniversityList();

		// operations - CRUD
		void appendNewNode(University*);
		void insertNodeAt(University*, int);
		void deleteNodeAtFront();
		void deleteNodeAtEnd();
		void deleteNodeAt(int);

		void displayNodesDetailsFromFront();
		void displayNodeDetailsFromEnd();

		// searching functions (returns one search results)
		University* searchByText(string, string);
		University* searchByNumeric(string, int);

		// filtering functions (returns multiple search results)
		UniversityList* filterName(string);
		UniversityList* filterScore(double, double);
		UniversityList* filterRank(int, int);

};

#endif
