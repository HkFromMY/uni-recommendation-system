#include "admin.h"
#include "util.h"
#include "common_interface.h"

void adminInterface() {
	system("cls");
	systemHeading();
	int selection = 0;

	while (selection != 5) {
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
	
	LinkedList<User>* userList = loadUserData("user.txt");
	Node<User>* currentNode = userList->getFirstNode();
	
	int selection = 0;
	int count = 1;
	while (selection != 3) {
		User* user = currentNode->getData();

		cout << "Previous Record - 1, Next Record - 2, Quit - 3" << endl;
		cout << "Record Count: " << count << endl;
		user->printDetails();
		
		cout << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				if (count == 1) {
					break;
				}
				else {
					currentNode = currentNode->getPreviousAddress();
					count--;
				}
				break;
			case 2:
				if (count == userList->getSize()) {
					break;
				}
				else {
					currentNode = currentNode->getNextAddress();
					count++;
				}
				break;
			case 3:
				cout << "Quitting record displays." << endl;
				break;
			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				systemHeading();
		}

		system("cls");
		systemHeading();
	}

}

void modifyUserDetails() {
	
}

void deleteUserAccount() {

}

void displayInactiveUser() {

}

void displayFeedbacks() {

}

void displayUniversities() {

}
