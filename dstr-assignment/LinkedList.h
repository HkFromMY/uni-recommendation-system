#pragma once
#ifndef Linkedlist_h
#define Linkedlist_h

#include "Node.h"
#include "University.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template <class Data>
class LinkedList
{
	// a doubly circular linked list that can traverse in two direction and
	// 1. from last element to first element
	// 2. from first element to last element

	private:
		Node<Data>* head;
		Node<Data>* last;
		int count;

	public:
		LinkedList();
		~LinkedList();

		// getters (read-only)
		Node<Data>* getFirstNode();
		Node<Data>* getLastNode();
		int getSize();

		// operations - CRUD
		void appendNewNode(Data*);
		void insertNodeAt(Data*, int);
		void deleteNodeAtFront();
		void deleteNodeAtEnd();
		void deleteNodeAt(int);

		void displayNodesDetailsFromFront();
		void displayNodeDetailsFromEnd();

};

template <class Data>
LinkedList<Data>::LinkedList() {
	head = NULL;
	count = 0;
	last = NULL;
}

template <class Data>
Node<Data>* LinkedList<Data>::getFirstNode() {
	return head;
}

template <class Data>
Node<Data>* LinkedList<Data>::getLastNode() {
	return last;
}

template <class Data>
int LinkedList<Data>::getSize() {
	return size;
}

template <class Data>
void LinkedList<Data>::appendNewNode(Data* newData) {
	// complexity O(1) as no loop involved

	Node<Data>* newNode = new Node<Data>(newData);

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
	//cout << "New node appended to the end of linked list." << endl;
}

template <class Data>
void LinkedList<Data>::insertNodeAt(Data* newData, int position) {
	// complexity O(N)

	// insert new node at 'position' argument given
	// this class use zero-based indexing so the first node has index 0

	Node<Data>* newNode = new Node<Data>(newData);

	if (head == NULL) {
		head = newNode;
		last = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);

		return;
	}

	if (position > count - 1) {
		// append to the end of the linked list
		appendNewNode(newData);

		return;
	}

	Node* currentNode = head;
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

template <class Data>
void LinkedList<Data>::deleteNodeAtFront() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	Node* nodeToBeDeleted = head;
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

template <class Data>
void LinkedList<Data>::deleteNodeAtEnd() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	Node* nodeToBeDeleted = last;
	last = last->getPreviousAddress();

	if (last != NULL) {
		last->setNextAddress(NULL);
	}
	else {
		head = NULL;
	}

	delete nodeToBeDeleted;
}

template <class Data>
void LinkedList<Data>::deleteNodeAt(int position) {
	// complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		return;
	}

	if (position > count - 1) {
		throw out_of_range("Index out of range!");
	}

	Node* currentNode = head;
	Node* previousNode = currentNode->getPreviousAddress();

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

template <class Data>
void LinkedList<Data>::displayNodesDetailsFromFront() {
	// time complexity O(N)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	// iterate through the linked list and print everything
	Node<Data>* currentNode = head;
	while (currentNode != NULL) {
		Data* currentData = currentNode->getData();
		currentData->printDetails();
		cout << string(50, '=') << endl;

		currentNode = currentNode->getNextAddress();
	}
}

template <class Data>
void LinkedList<Data>::displayNodeDetailsFromEnd() {
	// time complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	// iterate through the linked lsit and print everything
	Node* currentNode = last;
	while (currentNode != NULL) {
		University* currentUni = currentNode->getData();

		cout << "Institution Name --> " << currentUni->getInstitution() << endl;
		cout << "AR Rank --> " << currentUni->getARRank() << endl;
		cout << "AR Score --> " << currentUni->getARScore() << endl;
		cout << "Score scaled --> " << currentUni->getScoreScaled() << endl;
		cout << string(50, '=') << endl;

		currentNode = currentNode->getPreviousAddress();
	}
}

template <class Data>
LinkedList<Data>::~LinkedList() {}

#endif
