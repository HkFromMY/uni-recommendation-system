#include "user_model.h"

Node<User>* searchUser(Node<User>* headNode, int userId) {
	// source: https://www.prepbytes.com/blog/linked-list/binary-search-on-linked-list/
	// O(log n) - binary search

	if (headNode == NULL) return NULL;
	else if (headNode->getData()->getUserId() == userId) return headNode;

	// implements binary search on linkedlist
	Node<User>* first = headNode;
	Node<User>* end = NULL;

	do {
		Node<User>* middleNode = findMiddleUserNode(first, end);

		if (middleNode == NULL) return NULL;

		User* user = middleNode->getData();
		if (user->getUserId() == userId) {
			return middleNode;
		}
		else if (user->getUserId() < userId) {
			first = middleNode->getNextAddress();
		}
		else {
			end = middleNode;
		}

	} while (end == NULL || first != end);

	return NULL; // no results found
}

Node<User>* findMiddleUserNode(Node<User>* first, Node<User>* last) {
	// find the middle node between the first node and last node.
	if (first == NULL) return NULL;

	Node<User>* pointer_1 = first;
	Node<User>* pointer_2 = first->getNextAddress();

	while (pointer_2 != last) {
		pointer_2 = pointer_2->getNextAddress();

		if (pointer_2 != last) {
			pointer_1 = pointer_1->getNextAddress();
			pointer_2 = pointer_2->getNextAddress();

		}
	}

	return pointer_1;
}

// generate ids for records
int generateUserId(LinkedList<User>* currentUserList) {
	// this function generates new user id by incrementing to the latest user id by 1
	User* lastUser = currentUserList->getLastNode()->getData();

	int newUserId = lastUser->getUserId() + 1;

	return newUserId;
}

string latestUserRecordInString(LinkedList<User>* userList) {
	// return latest user record in string (identical to text file's records)
	// this function is called to generate a string that represents all user records in string to be written to the text file
	// O(N) time complexity

	int counter = 0;
	string output_text = "";
	Node<User>* current = userList->getFirstNode();

	while (counter < userList->getSize()) {

		output_text += current->getData()->toString();

		current = current->getNextAddress();
		counter++;
	}

	return output_text;
}

void updateLatestUserListOnFile(LinkedList<User>* latestUserList) {
	// get the latest user list and convert to string represented in text file
	string latestUserInString = latestUserRecordInString(latestUserList);

	// update on the text file
	writeToFile("user.txt", latestUserInString);
}

LinkedList<User>* filterUsersByRole(LinkedList<User>* users, int userRole) {
	// time complexity - O(N)
	LinkedList<User>* filteredUsers = new LinkedList<User>();
	Node<User>* currentNode = users->getFirstNode();

	while (currentNode != NULL) {
		if (currentNode->getData()->getRole() == userRole) {
			filteredUsers->appendNewNode(currentNode->getData());
		}

		currentNode = currentNode->getNextAddress();
	}

	return filteredUsers;
}

LinkedList<User>* loadUserData() {
	// load the user data from text file into LinkedList of User objects
	LinkedList<User>* user_list = new LinkedList<User>();
	string user_id, username, password, email, phone, role, last_login_date;
	ifstream file("user.txt");

	if (!file.is_open()) {
		cerr << "ERROR: File not found!" << endl;

		throw exception();
	}

	while (file.good()) {
		// get line by line
		getline(file, user_id, '|');
		getline(file, username, '|');
		getline(file, password, '|');
		getline(file, email, '|');
		getline(file, phone, '|');
		getline(file, role, '|');
		getline(file, last_login_date, '\n');

		if (user_id == "") {
			// ignore last row
			break;
		}

		User* user = new User(
			convertToInt(user_id),
			username,
			password,
			email,
			phone,
			role,
			new Date(last_login_date)
		);

		user_list->appendNewNode(user);

	}

	return user_list;
}

bool checkRecordUniqueness(LinkedList<User>* userList, string* username, string* email, string* phone) {
	// runs a linear search to check uniqueness of the username, email, and phone of a newly registered customer
	// time complexity - O(N)
	Node<User>* currentNode = userList->getFirstNode();
	while (currentNode != NULL) {
		User* user = currentNode->getData();

		if (user->getUsername() == *username) {
			cout << "Your username is taken!" << endl;

			return false;
		}
		else if (user->getEmail() == *email) {
			cout << "Your email is taken!" << endl;

			return false;
		}
		else if (user->getPhone() == *phone) {
			cout << "Your phone is taken!" << endl;

			return false;
		}

		currentNode = currentNode->getNextAddress();
	}

	return true;
}

bool checkRecordUniqueness(LinkedList<User>* userList, int userId, string* username, string* email, string* phone) {
	// runs a linear search to check uniqueness of the username, email, and phone of a newly registered customer
	// time complexity - O(N)
	Node<User>* currentNode = userList->getFirstNode();
	while (currentNode != NULL) {
		User* user = currentNode->getData();
		if (userId == user->getUserId()) {
			// no need check for existing customers
			currentNode = currentNode->getNextAddress();
			continue;
		}

		if (user->getUsername() == *username) {
			cout << "Your username is taken!" << endl;

			return false;
		}
		else if (user->getEmail() == *email) {
			cout << "Your email is taken!" << endl;

			return false;
		}
		else if (user->getPhone() == *phone) {
			cout << "Your phone is taken!" << endl;

			return false;
		}

		currentNode = currentNode->getNextAddress();
	}

	return true;
}