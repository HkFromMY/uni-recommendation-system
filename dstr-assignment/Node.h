#pragma once
#ifndef universitynode_h
#define universitynode_h

#include "University.h"

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <class Data>
class Node
{
	private:
		Node* next; 
		Data* data;
		Node* previous;

	public:
		// constructors
		Node(Data*);
		~Node();
		
		// getters
		Data* getData();
		Node<Data>* getNextAddress(); 
		Node<Data>* getPreviousAddress();

		// setters
		void setData(Data*);
		void setNextAddress(Node*); 
		void setPreviousAddress(Node*);

};

template <class Data>
Node<Data>::Node(Data* newData) {
	// address pointing to next node
	next = NULL;
	data = newData;
	previous = NULL;
}

// getters
template <class Data>
Data* Node<Data>::getData() { return data; }

template <class Data>
Node<Data>* Node<Data>::getNextAddress() { return next; }

template <class Data>
Node<Data>* Node<Data>::getPreviousAddress() { return previous; }

// setters
template <class Data>
void Node<Data>::setData(Data* newData) { data = newData; }

template <class Data>
void Node<Data>::setNextAddress(Node* nextAddress) { next = nextAddress; }

template <class Data>
void Node<Data>::setPreviousAddress(Node* previousAddress) { previous = previousAddress; }

template <class Data>
Node<Data>::~Node() {}

#endif

