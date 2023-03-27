#pragma once
#ifndef universitynode_h
#define universitynode_h

#include "University.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class UniversityNode
{
	private:
		UniversityNode* next; 
		University* data;
		UniversityNode* previous;

	public:
		// constructors
		UniversityNode(University*);
		
		// getters
		University* getData();
		UniversityNode* getNextAddress(); 
		UniversityNode* getPreviousAddress();

		// setters
		void setData(University*);
		void setNextAddress(UniversityNode*); 
		void setPreviousAddress(UniversityNode*);

};

extern UniversityNode* university_head;

#endif

