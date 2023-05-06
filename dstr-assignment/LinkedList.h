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

		// getters
		Node<Data>* getFirstNode();
		Node<Data>* getLastNode();
		int getSize();

		// setters
		void setFirstNode(Node<Data>*);
		void setLastNode(Node<Data>*);
		void setSize(int);

		// operations - CRUD
		void appendNewNode(Data*);
		void insertNodeAt(Data*, int);
		void deleteNodeAtFront();
		void deleteNodeAtEnd();
		void deleteNodeAt(int);
		void deleteThisNode(Node<Data>* node);

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
	return count;
}

template <class Data>
void LinkedList<Data>::setFirstNode(Node<Data>* newFirstNode) {
	head = newFirstNode;
}

template <class Data>
void LinkedList<Data>::setLastNode(Node<Data>* newLastNode) {
	last = newLastNode;
}

template <class Data>
void LinkedList<Data>::setSize(int newSize) {
	count = newSize;
}

template <class Data>
void LinkedList<Data>::appendNewNode(Data* newData) {
	// complexity O(1) as no loop involved

	Node<Data>* newNode = new Node<Data>(newData);

	if (head == NULL) {
		head = newNode;
		last = newNode;

	}
	else {
		// new node's previous address set to original last element's address
		newNode->setPreviousAddress(last);

		// set current node's next address to new node
		last->setNextAddress(newNode);

		// new last address becomes new node
		last = newNode;

	}

	count++;
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
		count++;

		return;
	}

	if (position > count - 1) {
		// append to the end of the linked list
		appendNewNode(newData);

		return;
	}

	Node<Data>* currentNode = head;
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

	Node<Data>* nodeToBeDeleted = head;
	head = head->getNextAddress(); // set new head to next address of the original head

	if (head != NULL) {
		// if the linked list have 2 or more elements before deleting
		head->setPreviousAddress(NULL);
	}
	else {
		last = NULL;

	}

	delete nodeToBeDeleted;
	count--;
}

template <class Data>
void LinkedList<Data>::deleteNodeAtEnd() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	Node<Data>* nodeToBeDeleted = last;
	last = last->getPreviousAddress();

	if (last != NULL) {
		// next address of last element will be NULL
		last->setNextAddress(NULL);

	}
	else {
		head = NULL;

	}

	delete nodeToBeDeleted;
	count--;
}

template <class Data>
void LinkedList<Data>::deleteNodeAt(int position) {
	// zero-based indexing
	// complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		return;
	}

	if (position > count - 1) {
		throw out_of_range("Index out of range!");
	}

	Node<Data>* currentNode = head;
	Node<Data>* previousNode = currentNode->getPreviousAddress();

	for (int currentIndex = 0; currentIndex <= position; currentIndex++) {

		if (currentIndex == position) 
		{	
			if (currentNode == head) {
				// if currentNode is head, then call deleteNodeAtFront
				deleteNodeAtFront();
			}
			else if (currentNode == last) {
				// if currentNode is last element, then call deleteNodeAtEnd
				deleteNodeAtEnd();
			}
			else {
				cout << "previousNode " << previousNode->getData()->getEmail() << endl;
				cout << "currentNode " << currentNode->getData()->getEmail() << endl;

				// reconnect the previous address of next node and next address of previous node after deleting the node
				previousNode->setNextAddress(currentNode->getNextAddress());
				currentNode->getNextAddress()->setPreviousAddress(previousNode);

				delete currentNode;
				count--;

			}

		}
		else {
			currentNode = currentNode->getNextAddress();
			previousNode = previousNode->getNextAddress();
		}
	}

}

template <class Data>
void LinkedList<Data>::deleteThisNode(Node<Data>* node) {
	// O(1) - time complexity
	// delete the node from the list
	// this functions ASSUMES that the node is from this LinkedList object
	if (node == NULL) {
		throw invalid_argument("'node' cannot be NULL!");

	}

	if (node == head) {
		deleteNodeAtFront();

	}
	else if (node == last) {
		deleteNodeAtEnd();

	}
	else {
		// delete the node and reduce linked list size by 1
		node->getPreviousAddress()->setNextAddress(node->getNextAddress());
		node->getNextAddress()->setPreviousAddress(node->getPreviousAddress());
		count--;

		delete node;
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
	Node<Data>* currentNode = last;
	while (currentNode != NULL) {
		University* currentUni = currentNode->getData();
		currentUni->printDetails();
		cout << string(50, '=') << endl;

		currentNode = currentNode->getPreviousAddress();
		
	}
}

template <class Data>
LinkedList<Data>::~LinkedList() { cout << "hi"; system("pause"); }

#endif
