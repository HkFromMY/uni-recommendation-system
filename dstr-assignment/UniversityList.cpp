#include "UniversityList.h"

UniversityList::UniversityList() {
	head = NULL;
	count = 0;
	last = NULL;
}

void UniversityList::appendNewNode(University* newUniversity) {
	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);
	}
	else {
		UniversityNode* currentNode = head;
		while (currentNode->getNextAddress() != head) {
			currentNode = currentNode->getNextAddress();
		}

		// raeching the last element

		// next address of current node becomes the new node
		currentNode->setNextAddress(newNode);

		// set the new node at the end of linked list
		newNode->setPreviousAddress(currentNode);
		
		// previous address of first node is updated to the new node
		head->setPreviousAddress(newNode);

		// next address of new node (last node) be the first node
		newNode->setNextAddress(head);
	}

	count++;
	cout << "New node appended to the end of linked list." << endl;
}

void UniversityList::insertNodeAt(University* newUniversity, int position) {
	// insert new node at 'position' argument given
	// this class use zero-based indexing so the first node has index 0

	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
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

void UniversityList::deleteNodeAt(int position) {
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

void UniversityList::displayNodesDetails() {
	if (head == NULL) {
		cout << "The linked list is empty!" << endl;
		return;
	}

	// iterate through the linked list and print everything
	UniversityNode* currentNode = head;
	int counter = 0;

	while (counter < count) {
		cout << "Previous Node Data --> " << currentNode->getPreviousAddress()->getData()->getInstitution() << endl;
		cout << "Current Node Data --> " << currentNode->getData()->getInstitution() << endl;
		cout << "Next Node Data --> " << currentNode->getNextAddress()->getData()->getInstitution() << endl << "-------------------------------------------------------------" << endl;

		currentNode = currentNode->getNextAddress();
		counter++;
	}
}

UniversityList::~UniversityList() {}