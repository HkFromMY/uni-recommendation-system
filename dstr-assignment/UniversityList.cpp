#include "UniversityList.h"

UniversityList::UniversityList() {
	head = NULL;
	count = 0;
	last = NULL;
}

void UniversityList::appendNewNode(University* newUniversity) {
	// complexity O(1) as no loop involved

	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
		last = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);
	}
	else {
		// original last element's next address becomes new node's address
		last->setNextAddress(newNode);

		// new node's previous address set to original last element's address
		newNode->setPreviousAddress(last);

		// new last address becomes new node
		last = newNode;

	}

	count++;
	cout << "New node appended to the end of linked list." << endl;
}

void UniversityList::insertNodeAt(University* newUniversity, int position) {
	// complexity O(N)

	// insert new node at 'position' argument given
	// this class use zero-based indexing so the first node has index 0

	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
		last = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);

		return;
	}

	if (position > count - 1) {
		// append to the end of the linked list
		appendNewNode(newUniversity);

		return;
	}

	UniversityNode* currentNode = head;
	for (int currentIndex = 0; currentIndex <= position; currentIndex++) {

		if (currentIndex == position - 1) {
			// set the previous address of original node at n position to new node
			currentNode->getNextAddress()->setPreviousAddress(newNode);

			// set the next address of new node to original node at n position
			newNode->setNextAddress(currentNode->getNextAddress());

			// set next address of current node to the new node
			currentNode->setNextAddress(newNode);

			// put previous address of new node to current node
			newNode->setPreviousAddress(currentNode);

			cout << "Node has been inserted!" << endl;
			count++;
			break;
		}

		currentNode = currentNode->getNextAddress();
	}

}

void UniversityList::deleteNodeAtFront() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		
		return;
	}

	UniversityNode* nodeToBeDeleted = head;
	head = head->getNextAddress(); // set new head to next address of the original head

	if (head != NULL) {
		// if the linked list have 2 or more elements, then set the previous address of new head to NULL
		head->setPreviousAddress(NULL);

	}
	else {
		last = NULL;

	}

	delete nodeToBeDeleted;
}

void UniversityList::deleteNodeAtEnd() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	UniversityNode* nodeToBeDeleted = last;
	last = last->getPreviousAddress();

	if (last != NULL) {
		last->setNextAddress(NULL);
	}
	else {
		head = NULL;
	}

	delete nodeToBeDeleted;
}

void UniversityList::deleteNodeAt(int position) {
	// complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		return;
	}

	if (position > count - 1) {
		throw out_of_range("Index out of range!");
	}

	UniversityNode* currentNode = head;
	UniversityNode* previousNode = currentNode->getPreviousAddress();

	for (int currentIndex = 0; currentIndex <= position; currentIndex++) {
		
		if (currentIndex == position) {
			// reconnect the previous address of next node and next address of previous node after deleting the node
			previousNode->setNextAddress(currentNode->getNextAddress());
			currentNode->getNextAddress()->setPreviousAddress(previousNode);

			if (currentNode == head) {
				// if currentNode is head, then reset the head also
				head = currentNode->getNextAddress();
			}

			delete currentNode;
			count--;
		}
		else {
			currentNode = currentNode->getNextAddress();
			previousNode = currentNode->getPreviousAddress();
		}
	}

}

void UniversityList::displayNodesDetailsFromFront() {
	// time complexity O(N)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	// iterate through the linked list and print everything
	UniversityNode* currentNode = head;
	while (currentNode != NULL) {
		cout << "Previous Node Data --> " << currentNode->getPreviousAddress()->getData()->getInstitution() << endl;
		cout << "Current Node Data --> " << currentNode->getData()->getInstitution() << endl;
		cout << "Next Node Data --> " << currentNode->getNextAddress()->getData()->getInstitution() << endl << "-------------------------------------------------------------" << endl;

		currentNode = currentNode->getNextAddress();
	}
}

void UniversityList::displayNodeDetailsFromEnd() {
	// time complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		
		return;
	}

	// iterate through the linked lsit and print everything
	UniversityNode* currentNode = last;
	while (currentNode != NULL) {
		cout << "Previous Node Data --> " << currentNode->getPreviousAddress()->getData()->getInstitution() << endl;
		cout << "Current Node Data --> " << currentNode->getData()->getInstitution() << endl;
		cout << "Next Node Data --> " << currentNode->getNextAddress()->getData()->getInstitution() << endl << "-------------------------------------------------------------" << endl;

		currentNode = currentNode->getPreviousAddress();
	}
}

// searching functions (returns one search results)
University* UniversityList::searchByText(string field, string target) {
	return new University(1, "asdasdasd");
}

University* UniversityList::searchByNumeric(string field, int target) {
	return new University(1, "asdasdasd");
}

// filtering functions (returns multiple search results)
UniversityList* UniversityList::filterName(string target) {
	return new UniversityList();
}

UniversityList* UniversityList::filterScore(double lower_range, double upper_range) {
	return new UniversityList();
}

UniversityList* UniversityList::filterRank(int lower_range, int upper_range) {
	return new UniversityList();
}

UniversityList::~UniversityList() {}