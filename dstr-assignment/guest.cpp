#include "guest.h"

void guestInterface(LinkedList<User>* currentUserList, LinkedList<University>* uniList) {
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
				displayAllUniversities(uniList);
				break;

			case 2:
				searchUniversityDetails(uniList);
				break;

			case 3:
				registerAsCustomer(currentUserList);
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

void displayAllUniversities(LinkedList<University>* allUniversities) {
	system("cls");
	systemHeading();

	LinkedList<University>* sortedUniversities = allUniversities->cloneLinkedList();

	int sortSelection;
	string sortFieldType = "text";
	string sortField = "uni_institution";
	cout << "Do you want to sort the universities by institution name before displaying? (1 - Yes, 2 - No) --> ";
	cin >> sortSelection;

	switch (sortSelection) {
		case 1: 
			// sort records
			sortedUniversities->setFirstNode(
				sortUniversities(
					sortedUniversities->getFirstNode(),
					&sortFieldType,
					&sortField,
					true // ascending order
				)
			);
			break;
		case 2:
			break;
		default:
			cout << "Invalid input!" << endl;
			system("pause");

			return displayAllUniversities(allUniversities);
	}

	// display records
	displayUniRecords(sortedUniversities);
}

void displayUniRecords(LinkedList<University>* uniList) {
	Node<University>* currentNode = uniList->getFirstNode();
	int selection = 0;
	
	while (selection != 3) {
		system("cls");
		systemHeading();

		currentNode->getData()->printDetails();
		cout << string(50, '=') << endl;

		if (currentNode->getPreviousAddress() == NULL) {
			cout << "1. Next" << endl;
			cout << "2. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1:
					currentNode = currentNode->getNextAddress();
					break;

				case 2:
					return;

				default:
					cout << "Invalid input!" << endl;
					system("pause");
					break;
			}

		}
		else if (currentNode->getNextAddress() == NULL) {
			cout << "1. Previous" << endl;
			cout << "2. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1:
					currentNode = currentNode->getPreviousAddress();
					break;

				case 2:
					return;

				default:
					cout << "Invalid input!" << endl;
					system("pause");
					break;
			}

		}
		else {
			cout << "1. Previous" << endl;
			cout << "2. Next" << endl;
			cout << "3. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (selection) {
				case 1:
					currentNode = currentNode->getPreviousAddress();
					break;
					
				case 2:
					currentNode = currentNode->getNextAddress();
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
}

void searchUniversityDetails(LinkedList<University>* allUniversities) {
	// search university menu
	bool reSearch = false; // users want to search again

	do {
		system("cls");
		systemHeading();

		// get the search field type and search field
		string selection = promptUserSearchField();
		if (selection == "") {

			return;
		}

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

				return searchUniversityDetails(allUniversities);
			}
		}
		else if (sortFieldType == "uni_rank") {
			bool validDigit = validateInteger(searchTarget);

			if (!validDigit) {
				cout << "The search value for rank is not valid! Please retry!" << endl;
				system("pause");

				return searchUniversityDetails(allUniversities);
			}
		}
		else if (sortFieldType == "score") {
			bool validDouble = validateDouble(searchTarget);

			if (!validDouble) {
				cout << "The search value for score is not valid! Please retry!" << endl;
				system("pause");

				return searchUniversityDetails(allUniversities);
			}
		}

		// sort the array according to the search field as binary search is implemented
		LinkedList<University>* sortedUniversities = allUniversities->cloneLinkedList();
		sortedUniversities->setFirstNode(
			sortUniversities(
				sortedUniversities->getFirstNode(),
				&sortFieldType,
				&sortField,
				true
			)
		);

		Node<University>* universityFound;
		if (sortFieldType == "uni_rank") {
			universityFound = searchUniversityByRank(
				sortedUniversities->getFirstNode(),
				&sortField,
				convertToInt(searchTarget)
			);
		}
		else if (sortFieldType == "text") {
			universityFound = searchUniversityByText(
				sortedUniversities->getFirstNode(),
				&sortField,
				&searchTarget
			);
		}
		else if (sortFieldType == "score") {
			universityFound = searchUniversityByScore(
				sortedUniversities->getFirstNode(),
				&sortField,
				convertToDouble(searchTarget)
			);
		}
		else {
			universityFound = searchUniversityByRankObj(
				sortedUniversities->getFirstNode(),
				&sortField,
				new Rank(searchTarget)
			);
		}

		reSearch = promptReSearch(universityFound);
	
	} while (reSearch);
}

bool promptReSearch(Node<University>* universityFound) {
	if (universityFound == NULL) {
		cout << "The target is not found!" << endl;
		system("pause");
		return true; // ask the user to search again
	}
	else {
		system("cls");
		systemHeading();

		universityFound->getData()->printDetails();
		cout << string(50, '=') << endl;

		int action = 0;
		cout << "Please select one of the options below." << endl;
		cout << "1. Search for another university." << endl;
		cout << "2. Quit" << endl;
		cout << "Enter your selection here --> ";
		cin >> action;

		switch (action) {
		case 1:
			return true;

		case 2:
			return false;

		default:
			cout << "Invalid input!" << endl;
			system("pause");

			return promptReSearch(universityFound);
		}
	}
}

void registerAsCustomer(LinkedList<User>* currentUserList) {
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


	bool isUniqueRecord = checkRecordUniqueness(currentUserList, &username, &email, &phone);
	if (!isUniqueRecord) {
		system("pause");
		return;
	}
	
	// creating new profile for user
	User* newCustomer = new User(
		generateUserId(currentUserList),
		username,
		password,
		email,
		phone,
		"user",
		new Date()
	);

	currentUserList->appendNewNode(newCustomer); // add newly registered customer to the linked list
	cout << "Registration Successful!" << endl;
	system("pause");
}
