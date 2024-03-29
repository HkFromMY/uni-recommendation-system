#include "favourite_model.h"

Node<Counter>* sortFavouritesByOccurrences(Node<Counter>* node) {
	if (node == NULL || node->getNextAddress() == NULL) {
		return node;
	}

	Node<Counter>* secondHalf = splitFavourites(node);

	// recursively sorted for first and second halves of the sub-linkedlist
	node = sortFavouritesByOccurrences(node);
	secondHalf = sortFavouritesByOccurrences(secondHalf);

	// merge sorted sub-linkedlist
	return mergeFavourites(node, secondHalf);
}

Node<Counter>* splitFavourites(Node<Counter>* headNode) {
	Node<Counter>* currentNode = headNode;
	Node<Counter>* nextNode = headNode;

	while (nextNode->getNextAddress() && nextNode->getNextAddress()->getNextAddress()) {
		nextNode = nextNode->getNextAddress()->getNextAddress();
		currentNode = currentNode->getNextAddress();
	}

	Node<Counter>* temp = currentNode->getNextAddress();
	currentNode->setNextAddress(NULL);

	return temp;
}

Node<Counter>* mergeFavourites(Node<Counter>* firstHalf, Node<Counter>* secondHalf) {
	if (firstHalf == NULL) return secondHalf;
	if (secondHalf == NULL) return firstHalf;

	// pick smaller values
	Counter* firstFavourite = firstHalf->getData();
	Counter* secondFavourite = secondHalf->getData();

	if (firstFavourite->getValue() > secondFavourite->getValue()) {
		firstHalf->setNextAddress(mergeFavourites(firstHalf->getNextAddress(), secondHalf));
		firstHalf->getNextAddress()->setPreviousAddress(firstHalf);
		firstHalf->setPreviousAddress(NULL);

		return firstHalf;
	}
	else {
		secondHalf->setNextAddress(mergeFavourites(firstHalf, secondHalf->getNextAddress()));
		secondHalf->getNextAddress()->setPreviousAddress(secondHalf);
		secondHalf->setPreviousAddress(NULL);

		return secondHalf;
	}
}

LinkedList<Favourite>* filterFavouriteByUser(LinkedList<Favourite>* favourites, int user_id) {
	// implements using linear search algorithm as multiple targets are returned
	// time complexity - O(N)
	LinkedList<Favourite>* user_favourites = new LinkedList<Favourite>();
	Node<Favourite>* currentNode = favourites->getFirstNode();
	while (currentNode != NULL) {
		if (currentNode->getData()->getUserId() == user_id) {
			user_favourites->appendNewNode(currentNode->getData());
		}

		currentNode = currentNode->getNextAddress();
	}

	return user_favourites;
}

// binary search implementation
Node<Favourite>* searchFavourite(LinkedList<Favourite>* favList, int favouriteId) {
	// search for favourite based on user id and delete
	
	Node<Favourite>* firstNode = favList->getFirstNode();
	Node<Favourite>* endNode = NULL;
	if (firstNode == NULL) return NULL;

	do {
		Node<Favourite>* middleNode = findMiddleFavouriteNode(firstNode, endNode);
		int middleFavouriteId = middleNode->getData()->getFavouriteId();

		if (middleFavouriteId == favouriteId) {
			// found target and delete
			return middleNode;

		}
		else if (middleFavouriteId < favouriteId) {
			firstNode = middleNode->getNextAddress();

		}
		else {
			endNode = middleNode;

		}


	} while (endNode == NULL || endNode != firstNode);

	return NULL;
}

Node<Favourite>* findMiddleFavouriteNode(Node<Favourite>* firstNode, Node<Favourite>* lastNode) {
	if (firstNode == NULL) return NULL;

	Node<Favourite>* pointer_1 = firstNode;
	Node<Favourite>* pointer_2 = firstNode->getNextAddress();

	while (pointer_2 != lastNode) {
		pointer_2 = pointer_2->getNextAddress();
		
		if (pointer_2 != lastNode) {
			pointer_1 = pointer_1->getNextAddress();
			pointer_2 = pointer_2->getNextAddress();

		}
	}

	return pointer_1;
}

LinkedList<Favourite>* loadFavouriteData() {
	LinkedList<Favourite>* favourite_list = new LinkedList<Favourite>();
	string favourite_id, user_id, favourite_university;
	ifstream file("favourite.txt");

	if (!file.is_open()) {
		cerr << "ERROR: File not found!" << endl;

		throw exception();
	}

	// parse data and return list of favourite objects
	while (file.good()) {
		getline(file, favourite_id, '|');
		getline(file, user_id, '|');
		getline(file, favourite_university, '\n');

		if (favourite_id == "") {
			break;
		}

		Favourite* favourite_uni = new Favourite(
			convertToInt(favourite_id),
			convertToInt(user_id),
			favourite_university
		);

		favourite_list->appendNewNode(favourite_uni);
	}

	return favourite_list;
}

HashMap<string, int>* loadFavouriteOccurrences() {
	// loads the favourites from text file into HashMap object
	HashMap<string, int>* favourite_occurrences = new HashMap<string, int>(2000);
	string favourite_id, user_id, favourite_university;
	ifstream file("favourite.txt");

	if (!file.is_open()) {
		cerr << "ERROR: File not found!" << endl;

		throw exception();
	}

	// parse data and return list of favourite objects
	while (file.good()) {
		getline(file, favourite_id, '|');
		getline(file, user_id, '|');
		getline(file, favourite_university, '\n');

		if (favourite_id == "") {
			break;
		}

		// keep track of the count
		favourite_occurrences->incrementCount(favourite_university);
	}

	return favourite_occurrences;
}

int generateFavouriteId() {
	LinkedList<Favourite>* favList = loadFavouriteData();
	Favourite* lastFavourite = favList->getLastNode()->getData();

	int newFavouriteId = lastFavourite->getFavouriteId() + 1;
	delete favList; // free memory

	return newFavouriteId;
}

void addNewFavouriteOnFile(int userId, Favourite* newFavourite) {
	// validations to make sure this university is unique in the user's fav list
	LinkedList<Favourite>* favList = loadFavouriteData();
	favList = filterFavouriteByUser(favList, userId);

	// simple linear search to search through the favourite list
	Node<Favourite>* currentNode = favList->getFirstNode();
	while (currentNode != NULL) {
		if (currentNode->getData()->getFavouriteUniversity() == newFavourite->getFavouriteUniversity()) {

			throw "This university is already saved by the users!";
		}

		currentNode = currentNode->getNextAddress();
	}

	// append new line of favourite object in file
	appendToFile("favourite.txt", newFavourite->toString());

	delete favList; // free memory
}

void deleteFavouriteOnFile(int favouriteId) {
	// search and delete favourite based on the favourite ID
	LinkedList<Favourite>* favList = loadFavouriteData();
	favList->deleteThisNode(searchFavourite(favList, favouriteId));

	// update on text file
	string latestFavouritesRecords = latestFavouritesInString(favList);
	writeToFile("favourite.txt", latestFavouritesRecords);

	delete favList; // free memory
}

string latestFavouritesInString(LinkedList<Favourite>* favList) {
	// convert latest favourite linked list into string to be outputted into the text file
	Node<Favourite>* currentNode = favList->getFirstNode();
	string outputText = "";

	while (currentNode != NULL) {
		outputText += currentNode->getData()->toString();
	
		currentNode = currentNode->getNextAddress();
	}

	return outputText;
}