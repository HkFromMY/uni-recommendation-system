#include "user_model.h"

// functions to conduct CRUD operations on txt files
void editUserOnFile(int userId, string newUsername, string newPassword, string newEmail, string newPhone) {
	// list of all users (including admins and users)
	LinkedList<User>* allUserList = loadUserData("user.txt");

	Node<User>* userToEdit = searchUser(allUserList->getLastNode(), userId);
	if (userToEdit == NULL) {
		cout << "User not found!" << endl;
		return;
	}

	// update the node found
	User* user = userToEdit->getData();
	user->setUsername(newUsername);
	user->setPassword(newPassword);
	user->setEmail(newEmail);
	user->setPhone(newPhone);

	// convert the user records in linked list to string (to be written on text file)
	string output_text = latestUserRecordInString(allUserList);

	// write the user records represented in text constructed above in text file
	writeToFile("user.txt", output_text);
}

void deleteUserOnFile(int userId) {
	LinkedList<User>* allUserList = loadUserData("user.txt");

	Node<User>* userToBeDeleted = searchUser(allUserList->getLastNode(), userId);
	if (userToBeDeleted == NULL) {
		cout << "User not found!" << endl;
		return;
	}

	// delete the found user node from the list
	allUserList->deleteThisNode(userToBeDeleted);

	// convert the user records in linked list to string (to be written on text file)
	string output_text = latestUserRecordInString(allUserList);

	// write the user records represented in text constructed above in text file
	writeToFile("user.txt", output_text);
}

Node<User>* searchUser(Node<User>* headNode, int userId) {
	// O(log n) - binary search

	if (headNode == NULL) {
		return NULL;

	}
	else if (headNode->getData()->getUserId() == userId) {
		// return head node if the target is in first node
		return headNode;

	}
	else if (headNode->getPreviousAddress()->getData()->getUserId() == userId) {
		// return last node if the target is in last node as binary search cannot handle if the last node contains target (for doubly circular linked list)
		return headNode->getPreviousAddress();

	}

	// implements binary search on linkedlist
	Node<User>* first = headNode;
	Node<User>* end = headNode->getPreviousAddress();
	Node<User>* middleNode;

	while (first != end) {
		middleNode = findMiddleUserNode(first, end);

		User* user = middleNode->getData();
		if (user->getUserId() == userId) {
			return middleNode;

		}
		else if (user->getUserId() < userId) {
			first = middleNode->getNextAddress();

		}
		else if (user->getUserId() > userId) {
			end = middleNode->getPreviousAddress();

		}
	}

	return NULL; // no results found
}

Node<User>* findMiddleUserNode(Node<User>* first, Node<User>* last) {
	// find the middle node between the first node and last node.

	Node<User>* pointer_1 = first;
	Node<User>* pointer_2 = first->getNextAddress();

	while (pointer_2 != last && pointer_2->getNextAddress() != last) {
		pointer_1 = pointer_1->getNextAddress();
		pointer_2 = pointer_2->getNextAddress()->getNextAddress();
	}

	return pointer_1;
}

// generate ids for records
int generateUserId() {
	// this function generates new user id by incrementing to the latest user records by 1
	LinkedList<User>* userList = loadUserData("user.txt");
	User* lastUser = userList->getLastNode()->getData();

	return lastUser->getUserId() + 1;
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

LinkedList<User>* loadUserData(string filepath) {
	// load the user data from text file into LinkedList of User objects
	LinkedList<User>* user_list = new LinkedList<User>();
	string user_id, username, password, email, phone, role, last_login_date;
	ifstream file(filepath);

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