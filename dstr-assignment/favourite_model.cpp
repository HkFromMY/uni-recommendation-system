#include "favourite_model.h"

Node<Counter>* sortFavouritesByOccurrences(Node<Counter>* node) {
	// sort favourite counter linked list by descending order according to the saved count of users
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

HashMap<string, int>* loadFavouriteOccurrences(LinkedList<Favourite>* allFavourites) {
	// convert favourite linked list into hash map
	HashMap<string, int>* favourite_occurrences = new HashMap<string, int>(2000);
	Node<Favourite>* currentNode = allFavourites->getFirstNode();

	while (currentNode != NULL) {
		Favourite* favourite = currentNode->getData();

		// tracking counts
		favourite_occurrences->incrementCount(favourite->getFavouriteUniversity());

		currentNode = currentNode->getNextAddress();
	}

	return favourite_occurrences;
}

int generateFavouriteId(LinkedList<Favourite>* favList) {
	Favourite* lastFavourite = favList->getLastNode()->getData();

	int newFavouriteId = lastFavourite->getFavouriteId() + 1;

	return newFavouriteId;
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

void updateLatestFavouritesOnTextFile(LinkedList<Favourite>* allFavourites) {
	// represent latest favourite list in string
	string latestFavourites = latestFavouritesInString(allFavourites);

	// write to the text file of that latest favourites
	writeToFile("favourite.txt", latestFavourites);
}
