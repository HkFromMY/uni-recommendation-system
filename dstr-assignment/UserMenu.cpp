#include "admin.h"
#include "util.h"
#include "common_interface.h"
#include "search.h"
#include "input_validation.h"
#include "login.h"
#include "UserMenu.h"
#include "University.h"

void userInterface() {
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
				userInterface();
				break;

		}
	}
}

void displayUniversityDetails() {
	sortOptions();
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

