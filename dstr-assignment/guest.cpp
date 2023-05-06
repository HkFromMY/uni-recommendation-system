#include "guest.h"

void guestInterface() {
	int selection = 0;
	while (selection != 4) {
		system("cls");
		systemHeading();
		cout << "Hello there, you can: " << endl;
		cout << "1. Display all university records" << endl;
		cout << "2. Search university details" << endl;
		cout << "3. Register as new customer" << endl;
		cout << "4. Quit the system" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				displayAllUniversities();
				break;

			case 2:
				searchUniversityDetails();
				break;

			case 3:
				registerAsCustomer();
				break;
			
			case 4:
				return;

			default:
				cout << "Invalid input!" << endl;
				system("pause");
				break;
		}
	}
}

void displayAllUniversities() {
	system("cls");
	systemHeading();

	LinkedList<University>* uniList = loadUniversitiesData();
	int sortSelection;
	string sortFieldType = "text";
	string sortField = "uni_institution";

	cout << "Do you want to sort the universities by institution name before displaying? (1 - Yes, 2 - No) --> ";
	cin >> sortSelection;

	// sort records
	uniList->setFirstNode(
		sortUniversities(
			uniList->getFirstNode(),
			&sortFieldType,
			&sortField,
			true // ascending order
		)
	);

	// display records
	displayUniRecords(uniList);

	delete uniList; // free memory
}

void displayUniRecords(LinkedList<University>* uniList) {
	Node<University>* currentNode = uniList->getFirstNode();
	int selection = 0;
	
	while (selection != 3) {
		system("cls");
		systemHeading();

		currentNode->getData()->printDetails();
		cout << string(50, '=') << endl;

		cout << "1. Previous" << endl;
		cout << "2. Next" << endl;
		cout << "3. Quit" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				if (currentNode->getPreviousAddress() != NULL) currentNode = currentNode->getPreviousAddress();
				else currentNode = uniList->getLastNode(); // go to the last element
				break;

			case 2:
				if (currentNode->getNextAddress() != NULL) currentNode = currentNode->getNextAddress();
				else currentNode = uniList->getFirstNode(); // go back to first element
				break;

			case 3:
				return;

			default:
				cout << "Invalid input!" << endl;
				system("pause");
				break;
		}
	}
}

void searchUniversityDetails() {
	// search university menu
	system("cls");
	systemHeading();
	LinkedList<University>* uniList = loadUniversitiesData();

	// get the search field type and search field
	string selection = promptUserSearchField();
	stringstream ss(selection);
	string sortFieldType, sortField;
	getline(ss, sortFieldType, '|');
	getline(ss, sortField, '|');

	string searchTarget;
	cout << "Please enter your search value: ";
	getline(cin, searchTarget, '\n');

	// basic validation for rank
	if (sortFieldType == "rank_obj") {
		bool validRank = validateRank(searchTarget);

		if (!validRank) {
			cout << "The search value for rank is not valid! Please retry!" << endl;
			system("pause");

			delete uniList;
			return searchUniversityDetails();
		}
	}

	// sort the array according to the search field as binary search is implemented
	uniList->setFirstNode(
		sortUniversities(
			uniList->getFirstNode(),
			&sortFieldType,
			&sortField,
			true
		)
	);

	Node<University>* universityFound;
	if (sortFieldType == "uni_rank") {
		universityFound = searchUniversityByRank(
			uniList->getFirstNode(),
			&sortField,
			convertToInt(searchTarget)
		);
	}
	else if (sortFieldType == "text") {
		universityFound = searchUniversityByText(
			uniList->getFirstNode(),
			&sortField,
			&searchTarget
		);
	}
	else if (sortFieldType == "score") {
		universityFound = searchUniversityByScore(
			uniList->getFirstNode(),
			&sortField,
			convertToDouble(searchTarget)
		);
	}
	else {
		universityFound = searchUniversityByRankObj(
			uniList->getFirstNode(),
			&sortField,
			new Rank(searchTarget)
		);
	}

	if (universityFound == NULL) {
		cout << "The target is not found!" << endl;
	}
	else {
		system("cls");
		systemHeading();

		universityFound->getData()->printDetails();
	}

	int action = 0;
	cout << "Please select one of the options below." << endl;
	cout << "1. Search for another university." << endl;
	cout << "2. Quit" << endl;
	cout << "Enter your selection here --> " << endl;
	cin >> action;

	switch (action) {
		case 2:
			return searchUniversityDetails();

		case 3:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");

			break;
	}

	delete uniList;
}

void registerAsCustomer() {
	system("cls");
	systemHeading();

	// getting inputs
	string username, password, email, phone;
	cout << "Registering an account for you..." << endl;
	cout << "Your username --> ";
	getline(cin, username, '\n');

	cout << "Your password --> ";
	getline(cin, password, '\n');

	cout << "Your email --> ";
	getline(cin, email, '\n');

	cout << "Your phone number --> ";
	getline(cin, phone, '\n');

	// validations
	bool validEmail = validateEmail(email);
	bool validPhone = validatePhone(phone);

	if (!validEmail) {
		cout << "The email is invalid!" << endl;
		system("pause");
		return;
	}
	else if (!validPhone) {
		cout << "The phone number is invalid!" << endl;
		system("pause");
		return;
	}

	bool isUniqueRecord = checkRecordUniqueness(&username, &email, &phone);
	if (!isUniqueRecord) {
		system("pause");
		return registerAsCustomer();
	}
	
	// creating new profile for user
	User* newCustomer = new User(
		generateUserId(),
		username,
		password,
		email,
		phone,
		"user",
		new Date()
	);

	// update on text file
	addNewUserOnFile(newCustomer);
	cout << "Registration Successful!" << endl;
	system("pause");
}

bool checkRecordUniqueness(string* username, string* email, string* phone) {
	// runs a linear search to check uniqueness of the username, email, and phone of a newly registered customer
	// time complexity - O(N)
	LinkedList<User>* userList = loadUserData();
	
	Node<User>* currentNode = userList->getFirstNode();
	while (currentNode != NULL) {
		User* user = currentNode->getData();

		if (user->getUsername() == *username) {
			cout << "Your username is taken!" << endl;
			delete userList;
			return false;
		}
		else if (user->getEmail() == *email) {
			cout << "Your email is taken!" << endl;
			delete userList;
			return false;
		}
		else if (user->getPhone() == *phone) {
			cout << "Your phone is taken!" << endl;
			delete userList;
			return false;
		}

		currentNode = currentNode->getNextAddress();
	}

	delete userList; // free memory
	return true;
}
