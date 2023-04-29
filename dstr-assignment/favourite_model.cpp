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