#include "admin.h"
#include "util.h"
#include "common_interface.h"
#include "search.h"
#include "input_validation.h"

void adminInterface() {
	int selection = 0;

	while (selection != 5) {
		system("cls");
		systemHeading();

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
				break;

			case 4:
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				adminInterface();
				break;
		}
	}
}

void displayRegisteredUserDetails() {
	system("cls");
	systemHeading();

	// loads in the user records
	LinkedList<User>* userList = loadUserData("user.txt", true);
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

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				currentNode = currentNode->getPreviousAddress();
				if (count == 1) count = userList->getSize();
				else count--;
				break;

			case 2:
				currentNode = currentNode->getNextAddress();
				if (count == userList->getSize()) count = 1;
				else count++;
				break;

			case 3:
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

			case 4:
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

			case 5:
				return;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				systemHeading();
				break;
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
	LinkedList<User>* userList = loadUserData("user.txt", true);
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

void displayFeedbacks() {

}

void displayUniversities() {

}

// functions to conduct CRUD operations on txt files
void editUserOnFile(int userId, string newUsername, string newPassword, string newEmail, string newPhone) {
	// list of all users (including admins and users)
	LinkedList<User>* allUserList = loadUserData("user.txt", false);

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
	LinkedList<User>* allUserList = loadUserData("user.txt", false);

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
