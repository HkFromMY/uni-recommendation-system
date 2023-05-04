#include "UserMenu.h"

void userInterface(User* userLoggedIn) {
	int selection = 0;

	while (selection != 5) {
		system("cls");
		systemHeading();

		cout << "Please select your action: " << endl;
		cout << "1. Display university records" << endl;
		cout << "2. Search university records" << endl;
		cout << "3. Display saved universities" << endl;
		cout << "4. Display sent feedbacks" << endl;
		cout << "5. Display received feedback replies" << endl;
		cout << "6. Log out from the system" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		//clear remaining string elements after extracting the integer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				displayUniversityDetails();
				break;

			case 2:
				searchUniversity();
				break;

			case 3:
				displaySavedUniversities();
				break;

			case 4:
				displayFeedback();
				break;

			case 5:
				displayFeedbackReplies();
				break;

			case 6:
				loginInterface();
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				userInterface(userLoggedIn);
				break;

		}
	}
}

void displayUniversityDetails() {
	// display university records 10 per page then the users can traverse back and forth
	// before entering this interface the users can select whether to sort the universities by what field in ascending or descending order
	system("cls");
	systemHeading();

	LinkedList<University>* uniList = loadUniversitiesData();
	int sortSelection;
	cout << "Do you want to sort the universities before displaying? (1 - Yes, 2 - No) --> ";
	cin >> sortSelection;

	if (sortSelection == 1) {

		system("cls");
		systemHeading();
		int fieldSelection;

		cout << "Which field of the university you wish to sort by: " << endl;
		cout << "1. Academic Reputation Score (AR Score)" << endl;
		cout << "2. Faculty/Student Ratio Score (FSR Score)" << endl;
		cout << "3. Employer Reputation Score (ER Score)" << endl;
		cout << "Enter your selection here --> ";
		cin >> fieldSelection;

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		string sortFieldType = "score";
		string sortField;
		if (fieldSelection == 1) {
			sortField = "uni_ar_score";
		}
		else if (fieldSelection == 2) {
			sortField = "uni_fsr_score";
		}
		else if (fieldSelection == 3) {
			sortField = "uni_er_score";
		}
		else {
			cout << "Invalid input!" << endl;
			return displayUniversityDetails();
		}

		// sort the uniList and replaces the unsorted one
		uniList->setFirstNode(
			sortUniversities(
				uniList->getFirstNode(),
				&sortFieldType,
				&sortField,
				false // descending order
			)
		);

	}
	else {
		return displayUniversityDetails();

	}
	
	displayUniversityRecords(uniList);

}

void displayUniversityRecords(LinkedList<University>* uniList) {
	// display the university records 10 by 10
	system("cls");
	systemHeading();

	Node<University>* currentNode = uniList->getFirstNode();
	int selection = 0;

	while (selection != 3) {
		system("cls");
		systemHeading();

		// print uni details
		currentNode->getData()->printDetails();
		cout << string(50, '=') << endl;

		// ask for action
		cout << "1. Next" << endl;
		cout << "2. Previous" << endl;
		cout << "3. Quit" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear string elements in input stream
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				if (currentNode->getNextAddress() != NULL) currentNode = currentNode->getNextAddress();
				else currentNode = uniList->getFirstNode(); // go back to first element
				break;

			case 2:
				if (currentNode->getPreviousAddress() != NULL) currentNode = currentNode->getPreviousAddress();
				else currentNode = uniList->getLastNode(); // go to the last element
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

void searchUniversity() {

}

void displaySavedUniversities() {

}

void displayFeedback() {

}

void displayFeedbackReplies() {

}

bool promptUserAction(University* university, string action) {
	system("cls");
	systemHeading();

	int selection = 0;
	cout << "Are you sure you want to " << action << university->getInstitution() << " as your favourite?" << endl << endl;
	cout << "Actions: " << endl;
	cout << "1. Yes" << endl;
	cout << "2. No" << endl;
	cout << "Enter your selection here --> ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (selection) {
	case 1:
		// save university record here
		return true;

	case 2:
		// cancel saving university operation
		return false;

	default:
		cout << "Please choose a valid option!" << endl;
		system("pause");
		return promptUserAction(university, action);
	}
}

void sortOptions() {
	system("cls");
	systemHeading();

	int selection = 0;
	cout << "How do you want to sort the university records?" << endl;
	cout << "1. Sort by academic reputation score" << endl;
	cout << "2. Sort by employer reputation score" << endl;
	cout << "3. Sort by faculty/student ratio" << endl;
	cout << "Enter your selection here --> ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	string field;
	switch (selection) {
	case 1:
		field = "ar_score";

	case 2:
		field = "er_score";

	case 3:
		field = "fsr_score";

	default:
		cout << "Please choose a valid option!" << endl;
		system("pause");
		return sortOptions();
	}
}

