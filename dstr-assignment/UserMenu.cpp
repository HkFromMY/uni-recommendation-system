#include "UserMenu.h"

void userInterface(User* userLoggedIn) {
	int selection = 0;

	while (selection != 7) {
		system("cls");
		systemHeading();
		cout << "Hello " << userLoggedIn->getUsername() << "!" << endl << endl;

		cout << "Please select your action: " << endl;
		cout << "1. Display university records" << endl;
		cout << "2. Search university records" << endl;
		cout << "3. Display saved universities" << endl;
		cout << "4. Display sent feedbacks" << endl;
		cout << "5. Display received feedback replies" << endl;
		cout << "6. Edit user profile" << endl;
		cout << "7. Log out from the system" << endl;
		cout << "Enter your selection here --> ";
		cin >> selection;

		//clear remaining string elements after extracting the integer
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (selection) {
			case 1:
				displayUniversityDetails(userLoggedIn);
				break;

			case 2:
				searchUniversityMenu(userLoggedIn);
				break;

			case 3:
				displaySavedUniversities(userLoggedIn);
				break;

			case 4:
				displayFeedback(userLoggedIn);
				break;

			case 5:
				displayFeedbackReplies(userLoggedIn);
				break;

			case 6:
				editUserProfile(userLoggedIn);
				break;

			case 7:
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				userInterface(userLoggedIn);
				break;

		}
	}
}

void displayUniversityDetails(User* userLoggedIn) {
	// before displaying uni details the users can select whether to sort the universities by what field in ascending or descending order
	system("cls");
	systemHeading();

	LinkedList<University>* uniList = loadUniversitiesData();
	int sortSelection;
	cout << "Do you want to sort the universities before displaying? (1 - Yes, 2 - No) --> ";
	cin >> sortSelection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

			delete uniList;
			return displayUniversityDetails(userLoggedIn);
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

		displayUniversityRecords(userLoggedIn, uniList);

	}
	else if (sortSelection == 2) {
		displayUniversityRecords(userLoggedIn, uniList);

	}
	else {
		// recursively call this function until the input is valid
		cout << "Invalid input!" << endl;
		system("pause");

		delete uniList;
		return displayUniversityDetails(userLoggedIn);

	}

	delete uniList; // free memory
}

void displayUniversityRecords(User* userLoggedIn, LinkedList<University>* uniList) {
	// display the university records 1 by 1
	Node<University>* currentNode = uniList->getFirstNode();
	int selection = 0;

	while (selection != 4) {
		system("cls");
		systemHeading();

		// print uni details
		currentNode->getData()->printDetails();
		cout << string(50, '=') << endl;

		// ask for action
		cout << "1. Previous" << endl;
		cout << "2. Next" << endl;
		cout << "3. Save as favourite." << endl;
		cout << "4. Quit" << endl;
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
				// save as favourite university
				saveUniversityAsFavourite(
					userLoggedIn,
					new Favourite(
						generateFavouriteId(),
						userLoggedIn->getUserId(),
						currentNode->getData()->getInstitution()
					)
				);
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

void searchUniversityMenu(User* userLoggedIn) {
	// search university menu
	// ask users which field to search before searching
	// only returns 1 result and call printDetails to print its details.

	int action = 0;
	LinkedList<University>* uniList = loadUniversitiesData();
	while (action != 3) {
		system("cls");
		systemHeading();

		// get the search field type and search field
		string selection = promptUserSearchField();
		if (selection == "") {
			delete uniList;
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

				delete uniList;
				return searchUniversityMenu(userLoggedIn);
			}
		}
		else if (sortFieldType == "uni_rank") {
			bool validDigit = validateInteger(searchTarget);

			if (!validDigit) {
				cout << "The search value for rank is not valid! Please retry!" << endl;
				system("pause");

				delete uniList;
				return searchUniversityMenu(userLoggedIn);
			}
		}
		else if (sortFieldType == "score") {
			bool validDouble = validateDouble(searchTarget);

			if (!validDouble) {
				cout << "The search value for score is not valid! Please retry!" << endl;
				system("pause");

				delete uniList;
				return searchUniversityMenu(userLoggedIn);
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

		action = promptAction(userLoggedIn, universityFound);

	}

	delete uniList; // free memory
}

int promptAction(User* userLoggedIn, Node<University>* universityFound) {
	int action = 0;
	if (universityFound == NULL) {
		cout << "The target is not found!" << endl;

		return 0; // re-run search menu
	}
	else {
		system("cls");
		systemHeading();
		universityFound->getData()->printDetails();
		cout << string(50, '=') << endl;

		cout << "Please select one of the options below." << endl;
		cout << "1. Save as favourite." << endl;
		cout << "2. Search for another university." << endl;
		cout << "3. Quit to user menu." << endl;
		cout << "Enter your selection here --> ";
		cin >> action;

		switch (action) {
			case 1:
				saveUniversityAsFavourite(
					userLoggedIn,
					new Favourite(
						generateFavouriteId(), // new id
						userLoggedIn->getUserId(),
						universityFound->getData()->getInstitution()
					)
				);
				return 1;

			case 2:
				return 2;

			case 3:
				return 3;

			default:
				cout << "Invalid input!" << endl;
				system("pause");

				return promptAction(userLoggedIn, universityFound);
		}
	}
}

void saveUniversityAsFavourite(User* userLoggedIn, Favourite* favouriteUniversity) {
	// confirm want to save then proceed
	int confirmSave = 0;
	cout << "Do you really want to save the university \"" << favouriteUniversity->getFavouriteUniversity() << "\" as favourite university? (1 - Yes, 2 - No) >> ";
	cin >> confirmSave;

	switch (confirmSave) {
		case 1:
			// save as favourite here
			try {
				addNewFavouriteOnFile(userLoggedIn->getUserId(), favouriteUniversity);
				cout << "The university has been successfully saved!" << endl;
				system("pause");
				return;

			}
			catch (const char* msg) {
				cerr << msg << endl;
				system("pause");

				return;
			}
			break;

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");

			return saveUniversityAsFavourite(userLoggedIn, favouriteUniversity);
	}
}

void displaySavedUniversities(User* userLoggedIn) {
	// display all favourite universities of that users
	system("cls");
	systemHeading();

	// filter favourite by users
	LinkedList<Favourite>* favList = loadFavouriteData();
	favList = filterFavouriteByUser(favList, userLoggedIn->getUserId());

	// print the favourite university out
	Node<Favourite>* currentNode = favList->getFirstNode();
	cout << "Favourite List: " << endl;
	int counter = 1;
	while (currentNode != NULL) {
		cout << counter << ". " << currentNode->getData()->getFavouriteUniversity() << endl;

		currentNode = currentNode->getNextAddress();
		counter++;
	}
	system("pause");
	delete favList; // free memory
}

void displayFeedback(User* userLoggedIn) {
	// show all the feedbacks sent, then give options to create 1
	system("cls");
	systemHeading();

	int counter = 1;
	LinkedList<Feedback>* userFeedbacks = loadFeedbackData();
	userFeedbacks = filterFeedbacksBySenderId(userFeedbacks, userLoggedIn->getUserId());
	Node<Feedback>* currentNode = userFeedbacks->getFirstNode();
	
	cout << "Feedbacks sent: " << endl;
	while (currentNode != NULL) {
		cout << counter << ". " << currentNode->getData()->getComment() << endl;
		counter++;

		currentNode = currentNode->getNextAddress();
	}

	cout << endl;
	int selection = 0;
	cout << "Please select one of the actions below: " << endl;
	cout << "1. Send a feedback." << endl;
	cout << "2. Go back to user interface." << endl;
	cout << "Enter your selection >> ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (selection) {
		case 1:
			sendFeedback(userLoggedIn);
			break;

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			break;
	}

	delete userFeedbacks; // free memory
}

void sendFeedback(User* userLoggedIn) {
	system("cls");
	systemHeading();

	string content;
	cout << "Enter your feedback message here: ";
	getline(cin, content, '\n');

	// get admin's id
	LinkedList<User>* userList = loadUserData();
	User* admin = filterUsersByRole(userList, ADMIN)->getFirstNode()->getData();

	Feedback* feedbackSent = new Feedback(
		generateFeedbackId(),
		userLoggedIn->getUserId(),
		admin->getUserId(),
		"User Feedback",
		content
	);

	// record on file
	appendNewFeedbackOnFile(feedbackSent);

	cout << "Feedback sent successfully!" << endl;
	system("pause");

	delete userList; // free memory
}

void displayFeedbackReplies(User* userLoggedIn) {
	// display feedback replies by the admin based on the latest date
	system("cls");
	systemHeading();
	cout << "Feedback Replies from Admin: " << endl << endl;

	// sort feedback replies from the admin (descending)
	LinkedList<Feedback>* feedbacks = loadFeedbackData();
	feedbacks = filterFeedbacksByRecipientId(feedbacks, userLoggedIn->getUserId());
	feedbacks->setFirstNode(
		sortFeedbackByDate(
			feedbacks->getFirstNode(),
			false // descending
		)
	);

	Node<Feedback>* currentNode = feedbacks->getFirstNode();
	while (currentNode != NULL) {
		cout << "Feedback send date: " << currentNode->getData()->getSendDate()->toString() << endl;
		cout << "Feedback content: " << currentNode->getData()->getComment() << endl;
		cout << string(50, '=') << endl;
		currentNode = currentNode->getNextAddress();
	}

	system("pause");

	delete feedbacks; // free memory
}

void editUserProfile(User* userLoggedIn) {
	system("cls");
	systemHeading();

	cout << "This is your current profile: " << endl;
	cout << "Username: " << userLoggedIn->getUsername() << endl;
	cout << "Email: " << userLoggedIn->getEmail() << endl;
	cout << "Phone: " << userLoggedIn->getPhone() << endl;

	int selection = 0;
	cout << "Do you want to edit your profile? (1 - Yes, 2 - No): ";
	cin >> selection;

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	switch (selection) {
		case 1: {
			// edit user profile here
			string newUsername, newPassword, newEmail, newPhone;

			cout << "New username: ";
			getline(cin, newUsername);

			cout << "New password: ";
			getline(cin, newPassword);

			cout << "New Email: ";
			getline(cin, newEmail);

			cout << "New Phone: ";
			getline(cin, newPhone);

			// validations
			bool validEmail = validateEmail(newEmail);
			bool validPhone = validatePhone(newPhone);

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

			bool isUniqueRecord = checkRecordUniqueness(userLoggedIn->getUserId(), &newUsername, &newEmail, &newPhone);
			if (!isUniqueRecord) {
				system("pause");
				return editUserProfile(userLoggedIn);
			}

			try {
				// edit user on text file
				editUserOnFile(userLoggedIn->getUserId(), newUsername, newPassword, newEmail, newPhone);

				// update immediate UI
				userLoggedIn->setUsername(newUsername);
				userLoggedIn->setPassword(newPassword); // not necessary
				userLoggedIn->setEmail(newEmail);
				userLoggedIn->setPhone(newPhone);

				cout << "User profile is edited successfully!" << endl;
				system("pause");

			}
			catch (const char* errorMsg) {
				cout << errorMsg << endl;
				system("pause");
				return;
			}
			
			break;
		}

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			return editUserProfile(userLoggedIn);
	}
}
