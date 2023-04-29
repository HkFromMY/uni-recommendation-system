#include "admin.h"

void adminInterface(User* userLoggedIn) {
	int selection = 0;

	while (selection != 5) {
		system("cls");
		systemHeading();

		cout << "Hello " << userLoggedIn->getUsername() << "!" << endl << endl;

		cout << "Please select your action: " << endl;
		cout << "1. Display user's records." << endl;
		cout << "2. Display inactive users." << endl;
		cout << "3. View feedback from users." << endl;
		cout << "4. Display top 10 universities' reports." << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear remaining string elements after extracting the int
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				displayRegisteredUserDetails();
				break;

			case 2:
				displayInactiveUser();
				break;

			case 3:
				displayFeedbacks(userLoggedIn);
				break;

			case 4:
				displayUniversities();
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				adminInterface(userLoggedIn);
				break;
		}
	}
}

void displayRegisteredUserDetails() {
	system("cls");
	systemHeading();

	// loads in the user records
	LinkedList<User>* userList = loadUserData("user.txt");
	userList = filterUsersByRole(userList, USER); // filters that only users are left

	int selection = 0;
	int count = 1;
	Node<User>* currentNode = userList->getFirstNode();

	while (selection != 5) {
		// display details and allows the users to navigate back and forth
		User* user = currentNode->getData();

		cout << "Record count: " << count << endl;
		user->printDetails();
		cout << endl;

		cout << "Actions: " << endl;
		cout << "1. Previous record." << endl;
		cout << "2. Next record." << endl;
		cout << "3. Edit user account." << endl;
		cout << "4. Delete user account." << endl;
		cout << "5. Quit." << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear string buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1: {
				if (count == 1) {
					// traverse to the last element
					currentNode = userList->getLastNode();
					count = userList->getSize();
				}
				else {
					// get previous element
					currentNode = currentNode->getPreviousAddress();
					count--;
				}

				break;

			}
			case 2: {
				if (count == userList->getSize()) {
					// traverse back to the first element
					currentNode = userList->getFirstNode();
					count = 1;
				}
				else {
					// get to the next element
					currentNode = currentNode->getNextAddress();
					count++;
				}
				
				break;

			}
			case 3: {
				// edit user account
				bool editUser;
				editUser = promptUserAction(user, "edit");

				if (editUser) {
					system("cls");
					systemHeading();

					string username, password, email, phone;
					cout << "New username --> ";
					getline(cin, username, '\n');

					cout << "New password --> ";
					getline(cin, password, '\n');

					cout << "New email --> ";
					getline(cin, email, '\n');
					bool validEmail = validateEmail(email);
					if (!validEmail) {
						cout << "Email not valid!" << endl;
						system("pause");
						break;
					}

					cout << "New phone --> ";
					getline(cin, phone, '\n');
					bool validPhone = validatePhone(phone);
					if (!validPhone) {
						cout << "Phone not valid!" << endl;
						system("pause");
						break;
					}

					editUserOnFile(user->getUserId(), username, password, email, phone);

					// immediate update
					user->setUsername(username);
					user->setPassword(password);
					user->setEmail(email);
					user->setPhone(phone);
				}

				break;
			}
			case 4: {
				// delete user account
				bool deleteUser;
				deleteUser = promptUserAction(user, "delete");

				// if confirmed that need to delete, then delete from LinkedList and txt file.
				if (deleteUser) {

					// delete this user record on txt file
					deleteUserOnFile(user->getUserId());

					// delete the node loaded in this function for immediate update on UI
					userList->deleteThisNode(currentNode);

					// get to first element after deletion
					currentNode = userList->getFirstNode(); // go back to first element
					count = 1;
				}

				break;

			}
			case 5:
				return;

			default: {
				cout << "Please choose a valid option!" << endl;
				system("pause");
				systemHeading();
				break;

			}
		}

		system("cls");
		systemHeading();
	}

}

bool promptUserAction(User* user, string action) {
	// this function prints confirmation message that asks the users whether they want to proceed with their action related to user's CRUD
	system("cls");
	systemHeading();

	int selection = 0;

	cout << "Are you sure you want to " << action << " the user with email : " << user->getEmail() << endl << endl;
	cout << "Actions: " << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << "Enter your selection here --> ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	// 1 for delete user record, 2 for returning to previous interface, if invalid choice then recursive call the function
	switch (selection) {
		case 1:
			// delete user record here
			return true;

		case 2:
			// quit deleting user interface
			return false;

		default:
			cout << "Please choose a valid option!" << endl;
			system("pause");
			return promptUserAction(user, action);
	}
}

void displayInactiveUser() {
	system("cls");
	systemHeading();
	
	// printing inactive users
	bool hasInactive = false;
	LinkedList<User>* userList = loadUserData("user.txt");
	userList = filterUsersByRole(userList, USER);

	Node<User>* currentNode = userList->getFirstNode();
	User* user;

	cout << "Inactive Users: " << endl;
	for (int i = 0; i < userList->getSize(); i++) {
		user = currentNode->getData();

		if (user->isInactive()) {
			cout << string(40, '=') << endl;
			user->printDetails();
			cout << string(40, '=') << endl;

			hasInactive = true;

		}

		currentNode = currentNode->getNextAddress();
	}

	if (!hasInactive) {
		cout << "No inactive users currently!" << endl;
		cout << "Quitting the interface now..." << endl;

		system("pause");

		return;
	}

	// Select user and delete on text file
	int userId;
	cout << "Which user's account you wish to delete? (Enter -1 to exit) --> ";
	cin >> userId;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (userId == -1) {
		return;

	}

	Node<User>* userToDelete = searchUser(userList->getFirstNode(), userId);
	if (userToDelete == NULL || !userToDelete->getData()->isInactive()) {
		// if user not found
		cout << "WARNING: User not found!" << endl;
		system("pause");
		displayInactiveUser();

	}
	else {
		// if user found
		bool deleteUser = promptUserAction(userToDelete->getData(), "delete");
		if (deleteUser) {
			// delete the users on text file
			deleteUserOnFile(userId);

		}
		else {
			// call again this interface
			displayInactiveUser();

		}
	}
}

void displayFeedbacks(User* userLoggedIn) {
	system("cls");
	systemHeading();

	// sort feedback by date
	LinkedList<Feedback>* feedbacks = loadFeedbackData("feedback.txt");
	feedbacks->setFirstNode(sortFeedbackByDate(feedbacks->getFirstNode()));
	feedbacks = filterFeedbacksByType(feedbacks, "User Feedback"); // filter so that only user feedback are remained

	int selection = 0;
	int count = 1;
	Node<Feedback>* currentNode = feedbacks->getFirstNode();

	while (selection != 4) {
		// display details and allows the users to navigate back and forth
		Feedback* feedback = currentNode->getData();

		cout << "Record count: " << count << endl;
		feedback->printDetails();
		cout << endl;

		cout << "Actions: " << endl;
		cout << "1. Previous record." << endl;
		cout << "2. Next record." << endl;
		cout << "3. Reply to feedback." << endl;
		cout << "4. Quit." << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear string buffer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1: {
				if (count == 1) {
					// traverse to the last element
					currentNode = feedbacks->getLastNode();
					count = feedbacks->getSize();
				}
				else {
					// get previous element
					currentNode = currentNode->getPreviousAddress();
					count--;
				}
				break;

			}
			case 2: {
				if (count == feedbacks->getSize()) {
					// traverse to the first element
					currentNode = feedbacks->getFirstNode();
					count = 1;
				}
				else {
					// get next element
					currentNode = currentNode->getNextAddress();
					count++;
				}
				break;

			}
			case 3: {
				// reply feedback to user
				cout << endl;
				string reply;

				cout << "Your reply to this feedback (-1 to cancel) --> ";
				getline(cin, reply, '\n');

				// simple validations
				if (reply == "-1") {
					break;

				} else if (reply == "") {
					cout << "The content of this reply message is invalid!" << endl;
					system("pause");

					break;
				}

				// append new feedback on the text file after passing validations
				Feedback* newFeedback = new Feedback(
					generateFeedbackId(),
					userLoggedIn->getUserId(), // admin id
					currentNode->getData()->getSenderId(), // recipient id which is the sender of this feedback replying to
					"Admin Reply",
					reply
				);
				appendNewFeedbackOnFile(newFeedback);
				cout << "Feedback has been sent successfully!" << endl;
				system("pause");

				break;

			}
			case 4:
				return;

			default: {
				cout << "Please choose a valid option!" << endl;
				system("pause");

				break;

			}
		}

		system("cls");
		systemHeading();
	}
}

void displayUniversities() {
	// display top 10 universities according to the favourites
	system("cls");
	systemHeading();
	cout << "Top 10 Universities according to parents' favourites:" << endl;
	cout << string(40, '=') << endl;

	// load favourite occurrences from favourites.txt and sort it by descending order
	LinkedList<Counter>* favourites = loadFavouriteOccurrences()->to_counters();
	favourites->setFirstNode(sortFavouritesByOccurrences(favourites->getFirstNode()));

	Node<Counter>* currentNode = favourites->getFirstNode();
	// print top 10 universities
	for (int counter = 0; counter < 10; counter++) {
		if (currentNode == NULL) {
			system("pause");
			return;
		}
		
		Counter* currentUni = currentNode->getData();
		cout << "Institution Name: " << currentUni->getKey() << endl;
		cout << "Number of parents who saved: " << currentUni->getValue() << endl;
		cout << string(50, '=') << endl;

		currentNode = currentNode->getNextAddress();
	}

	system("pause");
}
