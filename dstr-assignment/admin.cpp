#include "admin.h"

void adminInterface(
	User* userLoggedIn,
	LinkedList<User>* userList,
	LinkedList<University>* allUniversities,
	LinkedList<Feedback>* allFeedbacks,
	LinkedList<Favourite>* allFavourites
) {
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
		cout << "5. Log out from the system" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear remaining string elements after extracting the int
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				displayRegisteredUserDetails(userList);
				break;

			case 2:
				displayInactiveUser(userList);
				break;

			case 3:
				displayFeedbacks(userLoggedIn, allFeedbacks);
				break;

			case 4:
				displayUniversities(allUniversities, allFavourites);
				break;

			case 5:
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				adminInterface(userLoggedIn, userList, allUniversities, allFeedbacks, allFavourites);
				break;
		}
	}
}

void displayRegisteredUserDetails(LinkedList<User>* allUsers) {
	system("cls");
	systemHeading();

	// loads in the user records
	LinkedList<User>* userList = filterUsersByRole(allUsers, USER); // filters that only users are left

	int selection = 0;
	int count = 1;
	Node<User>* currentNode = userList->getFirstNode();

	while (true) {
		// display details and allows the users to navigate back and forth
		User* user = currentNode->getData();

		cout << "Record count: " << count << endl;
		user->printDetails();
		cout << endl;

		// selective UI
		if (currentNode->getPreviousAddress() == NULL) {
			cout << "Actions: " << endl;
			cout << "1. Next record." << endl;
			cout << "2. Edit user account." << endl;
			cout << "3. Delete user account." << endl;
			cout << "4. Quit." << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			// clear string buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1: {
					currentNode = currentNode->getNextAddress();
					count++;
					break;

				}
				case 2: {
					// edit user profile
					editUser(user, allUsers);
					break;

				}
				case 3: {
					// delete user node from global structure
					deleteUserAccount(user, allUsers);

					// delete user node from local user list structure for immediate UI update
					userList->deleteThisNode(currentNode); 

					currentNode = userList->getFirstNode();
					count = 1;
					break;
				}
				case 4: {
					return;

				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");
					systemHeading();
					break;

				}
			}


		}
		else if (currentNode->getNextAddress() == NULL) {
			cout << "Actions: " << endl;
			cout << "1. Previous record." << endl;
			cout << "2. Edit user account." << endl;
			cout << "3. Delete user account." << endl;
			cout << "4. Quit." << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			// clear string buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1: {
					currentNode = currentNode->getPreviousAddress();
					count--;
					break;

				}
				case 2: {
					// edit user profile
					editUser(user, allUsers);
					break;

				}
				case 3: {
					// delete user account
					deleteUserAccount(user, allUsers);

					// delete user node from local user list structure for immediate UI update
					userList->deleteThisNode(currentNode);

					currentNode = userList->getFirstNode();
					count = 1;
					break;
				}
				case 4: {
					return;

				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");
					systemHeading();
					break;

				}
			}

		}
		else {
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
					currentNode = currentNode->getPreviousAddress();
					count--;
					break;

				}
				case 2:
					currentNode = currentNode->getNextAddress();
					count++;
					break;

				case 3: {
					// edit user profile
					editUser(user, allUsers);
					break;

				}
				case 4: {
					// delete user account
					deleteUserAccount(user, allUsers);

					// delete user node from local user list structure for immediate UI update
					userList->deleteThisNode(currentNode);

					currentNode = userList->getFirstNode();
					count = 1;
					break;
				}
				case 5: {
					return;

				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");
					systemHeading();
					break;

				}
			}

		}

		system("cls");
		systemHeading();
	}
}

void editUser(User* userToEdit, LinkedList<User>* allUsers) {
	// edit user account
	bool editUser;
	editUser = promptUserAction(userToEdit, "edit");

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
			return;
		}

		cout << "New phone --> ";
		getline(cin, phone, '\n');
		bool validPhone = validatePhone(phone);
		if (!validPhone) {
			cout << "Phone not valid!" << endl;
			system("pause");
			return;
		}

		// check whether the new details exists such as username, email, and phone
		bool uniqueDetails = checkRecordUniqueness(allUsers, userToEdit->getUserId(), &username, &email, &phone);
		if (uniqueDetails) {
			// immediate update
			userToEdit->setUsername(username);
			userToEdit->setPassword(password);
			userToEdit->setEmail(email);
			userToEdit->setPhone(phone);
		}
	}
}

void deleteUserAccount(User* userToDelete, LinkedList<User>* allUsers) {
	// delete user account
	bool deleteUser;
	deleteUser = promptUserAction(userToDelete, "delete");

	// if confirmed that need to delete, then delete from LinkedList and txt file.
	if (deleteUser) {
		// delete the node loaded in this function for immediate update on UI
		Node<User>* deleteUserFromAll = searchUser(allUsers->getFirstNode(), userToDelete->getUserId());
		allUsers->deleteThisNode(deleteUserFromAll);

		cout << "The user account is deleted successfully!" << endl;
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

void displayInactiveUser(LinkedList<User>* allUsers) {
	system("cls");
	systemHeading();
	
	// printing inactive users
	bool hasInactive = false;
	LinkedList<User>* userList = filterUsersByRole(allUsers, USER); // filters only user role out
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
	cout << "Enter the user's id you wish to delete (Enter -1 to exit) --> ";
	cin >> userId;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (userId == -1) {
		return;

	}

	Node<User>* userToDelete = searchUser(allUsers->getFirstNode(), userId);
	if (userToDelete == NULL || !userToDelete->getData()->isInactive()) {
		// if user not found
		cout << "WARNING: User not found!" << endl;
		system("pause");

		return displayInactiveUser(allUsers);

	}
	else {
		// if user found
		bool deleteUser = promptUserAction(userToDelete->getData(), "delete");
		if (deleteUser) {
			// delete on the global user list data structure
			allUsers->deleteThisNode(userToDelete);

		}
		else {
			// show all the inactive users again if don't want to delete the user
			return displayInactiveUser(allUsers);

		}
	}
}

void displayFeedbacks(User* userLoggedIn, LinkedList<Feedback>* allFeedbacks) {
	system("cls");
	systemHeading();

	// sort feedback by date (descending)
	LinkedList<Feedback>* sortedFeedbacks = allFeedbacks->cloneLinkedList(); // clone new linked list for sorted display purposes
	sortedFeedbacks->setFirstNode(sortFeedbackByDate(sortedFeedbacks->getFirstNode(), false));
	sortedFeedbacks = filterFeedbacksByType(sortedFeedbacks, "User Feedback"); // filter so that only user feedback are remained

	int selection = 0;
	int count = 1;
	Node<Feedback>* currentNode = sortedFeedbacks->getFirstNode();

	while (true) {
		// display details and allows the users to navigate back and forth
		Feedback* feedback = currentNode->getData();

		cout << "Record count: " << count << endl;
		feedback->printDetails();
		cout << endl;

		if (currentNode->getPreviousAddress() == NULL) {
			cout << "Actions: " << endl;
			cout << "1. Next record." << endl;
			cout << "2. Reply to feedback." << endl;
			cout << "3. Quit." << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			// clear string buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1: {
					currentNode = currentNode->getNextAddress();
					count++;
					break;
				}

				case 2: {
					// reply feedback to user
					sendFeedbackReply(userLoggedIn, allFeedbacks, currentNode->getData()->getSenderId());

					currentNode = sortedFeedbacks->getFirstNode();
					count = 1;
					break;
				}

				case 3: {
					return;
				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");

					break;
				}
			}
		}
		else if (currentNode->getNextAddress() == NULL) {
			cout << "Actions: " << endl;
			cout << "1. Previous record." << endl;
			cout << "2. Reply to feedback." << endl;
			cout << "3. Quit." << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			// clear string buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1: {
					currentNode = currentNode->getPreviousAddress();
					count--;
					break;
				}

				case 2: {
					// reply feedback to users
					sendFeedbackReply(userLoggedIn, allFeedbacks, currentNode->getData()->getSenderId());
					
					currentNode = sortedFeedbacks->getFirstNode();
					count = 1;
					break;
				}

				case 3: {
					return;

				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");

					break;
				}
			}
		}
		else {
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
					currentNode = currentNode->getPreviousAddress();
					count--;
					break;
				}

				case 2: {
					currentNode = currentNode->getNextAddress();
					count++;
					break;
				}

				case 3: {
					// reply feedback to user
					sendFeedbackReply(userLoggedIn, allFeedbacks, currentNode->getData()->getSenderId());
					
					currentNode = sortedFeedbacks->getFirstNode();
					count = 1;
					break;
				}
				case 4: {
					return;

				}

				default: {
					cout << "Please choose a valid option!" << endl;
					system("pause");

					break;
				}
			}

		}

		system("cls");
		systemHeading();
	}
}

void sendFeedbackReply(User* userLoggedIn, LinkedList<Feedback>* allFeedbacks, int recipientId) {
	// reply feedback to user
	cout << endl;
	string reply;

	cout << "Your reply to this feedback (-1 to cancel) --> ";
	getline(cin, reply, '\n');

	// simple validations
	if (reply == "-1") {
		return;

	}
	else if (reply == "") {
		cout << "The content of this reply message is invalid!" << endl;
		system("pause");

		return;
	}

	// create new feedback object after passing validations
	Feedback* newFeedback = new Feedback(
		generateFeedbackId(allFeedbacks),
		userLoggedIn->getUserId(), // admin id
		recipientId, // recipient id which is the sender of this feedback replying to
		"Admin Reply",
		reply
	);
	allFeedbacks->appendNewNode(newFeedback); // append the new feedback to the global feedback list

	cout << "Feedback has been sent successfully!" << endl;
	system("pause");
}

void displayUniversities(LinkedList<University>* allUniversities, LinkedList<Favourite>* allFavourites) {
	// display top 10 universities according to the favourites
	system("cls");
	systemHeading();
	cout << "Top 10 Universities according to parents' favourites:" << endl;
	cout << string(40, '=') << endl;

	// load favourite occurrences from favourites.txt and sort it by descending order
	LinkedList<Counter>* favourites = loadFavouriteOccurrences(allFavourites)->to_counters();
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

	cout << endl;
	int selection = 0;
	cout << "Do you want to search for the details of the university?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << "Enter your selection >> ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (selection) {
		case 1: {
			string sortFieldType = "text";
			string sortField = "uni_institution";
			string searchUni;

			cout << "Feel free to copy the institution name and find further details about the university using the search function!" << endl;
			cout << "Enter your search here: ";
			getline(cin, searchUni, '\n');
			
			LinkedList<University>* sortedUniversities = allUniversities->cloneLinkedList();

			// sort universities before search
			sortedUniversities->setFirstNode(
				sortUniversities(
					sortedUniversities->getFirstNode(),
					&sortFieldType,
					&sortField,
					true
				)
			);

			// search universities
			Node<University>* uniFound = searchUniversityByText(sortedUniversities->getFirstNode(), &sortField, &searchUni);
			if (uniFound) {
				system("cls");
				systemHeading();
				cout << "Results: " << endl;
				uniFound->getData()->printDetails();

			}
			else {
				cout << "The searched university is not found!" << endl;

			}

			system("pause");
			return displayUniversities(allUniversities, allFavourites);
		}

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			return displayUniversities(allUniversities, allFavourites);
	}
}
