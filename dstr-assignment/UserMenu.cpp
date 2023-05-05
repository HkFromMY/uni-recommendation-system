#include "UserMenu.h"

void userInterface(User* userLoggedIn) {
	int selection = 0;

	while (selection != 5) {
		system("cls");
		systemHeading();
		cout << "Hello " << userLoggedIn->getUsername() << "!" << endl << endl;

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
				searchUniversityMenu();
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
	// before displaying uni details the users can select whether to sort the universities by what field in ascending or descending order
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
			system("pause");
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

		displayUniversityRecords(uniList);

	}
	else if (sortSelection == 2) {
		displayUniversityRecords(uniList);

	}
	else {
		// recursively call this function until the input is valid
		cout << "Invalid input!" << endl;
		system("pause");
		return displayUniversityDetails();

	}
}

void displayUniversityRecords(LinkedList<University>* uniList) {
	// display the university records 1 by 1
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
		cout << "1. Previous" << endl;
		cout << "2. Next" << endl;
		cout << "3. Quit" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		// clear string elements in input stream
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

void searchUniversityMenu() {
	// search university menu
	// ask users which field to search before searching
	// only returns 1 result and call printDetails to print its details.

	system("cls");
	systemHeading();
	LinkedList<University>* uniList = loadUniversitiesData();

	// get the sort field type and sort field
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

			return searchUniversityMenu();
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

	int searchAgain = 0;
	cout << "Do you want to search again (1 - Yes, 2 - No): ";
	cin >> searchAgain;

	if (searchAgain == 1) {
		return searchUniversityMenu();
	}
	else if (searchAgain == 2) {
		return;
	}
	else {
		cout << "Invalid input!" << endl;
		system("pause");
		return;
	}
}

void displaySavedUniversities() {

}

void displayFeedback() {

}

void displayFeedbackReplies() {

}

string promptUserSearchField() {
	// a utility function that converts integer (selection by users) into sort/search fields in string format
	// the string returned is in format "sortType|sortField" so the value returned need to be parsed
	
	int selection = 0;

	cout << "Which field do you want to search the universities by?" << endl;
	cout << "1. General Rank" << endl;
	cout << "2. Institution Name" << endl;
	cout << "3. Location Code" << endl;
	cout << "4. Location" << endl;
	cout << "5. Academic Reputation Score" << endl;
	cout << "6. Academic Reputation Rank" << endl;
	cout << "7. Employer Reputation Score" << endl;
	cout << "8. Employer Reputation Rank" << endl;
	cout << "9. Faculty/Student Ratio Score" << endl;
	cout << "10. Faculty/Student Ratio Rank" << endl;
	cout << "11. Citations per Faculty Score" << endl;
	cout << "12. Citations per Faculty Rank" << endl;
	cout << "13. International Faculty Ratio Score" << endl;
	cout << "14. International Faculty Ratio Rank" << endl;
	cout << "15. International Student Ratio Score" << endl;
	cout << "16. International Student Ratio Rank" << endl;
	cout << "17. International Research Network Score" << endl;
	cout << "18. International Research Network Rank" << endl;
	cout << "19. Employment Outcome Score (GER Score)" << endl;
	cout << "20. Employment Outcome Rank (GER Rank)" << endl;
	cout << "21. Score Scaled" << endl;
	cout << "Enter your selection here >> ";
	cin >> selection;

	// clear string elements
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	switch (selection) {
		case 1:
			return "uni_rank|uni_rank";
		case 2:
			return "text|uni_institution";
		case 3:
			return "text|uni_location_code";
		case 4:
			return "text|uni_location";
		case 5:
			return "score|uni_ar_score";
		case 6:
			return "rank_obj|uni_ar_rank";
		case 7:
			return "score|uni_er_score";
		case 8:
			return "rank_obj|uni_er_rank";
		case 9:
			return "score|uni_fsr_score";
		case 10:
			return "rank_obj|uni_fsr_rank";
		case 11:
			return "score|uni_cpf_score";
		case 12:
			return "rank_obj|uni_cpf_rank";
		case 13:
			return "score|uni_ifr_score";
		case 14:
			return "rank_obj|uni_ifr_rank";
		case 15:
			return "score|uni_isr_score";
		case 16:
			return "rank_obj|uni_isr_rank";
		case 17:
			return "score|uni_irn_score";
		case 18:
			return "rank_obj|uni_irn_rank";
		case 19:
			return "score|uni_ger_score";
		case 20:
			return "rank_obj|uni_ger_rank";
		case 21:
			return "score|uni_scored_scaled";
	}
}
