#include "UniversityNode.h"

UniversityNode::UniversityNode(University* newUniversity) {
	// address pointing to next node
	next = NULL;
    data = newUniversity;
    previous = NULL;
}

// getters
University* UniversityNode::getData() { return data; }
UniversityNode* UniversityNode::getNextAddress() { return next; }
UniversityNode* UniversityNode::getPreviousAddress() { return previous;  }

// setters
void UniversityNode::setData(University* newUniversity) { data = newUniversity; }
void UniversityNode::setNextAddress(UniversityNode* nextAddress) { next = nextAddress;}
void UniversityNode::setPreviousAddress(UniversityNode* previousAddress) { previous = previousAddress; }

UniversityNode::~UniversityNode() {}