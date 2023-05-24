#include "UserMenu.h"

void userInterface(User* userLoggedIn, LinkedList<User>* allUsers, LinkedList<University>* allUniversities, LinkedList<Feedback>* allFeedbacks, LinkedList<Favourite>* allFavourites) {
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
				displayUniversityDetails(userLoggedIn, allUniversities, allFavourites);
				break;

			case 2:
				searchUniversityMenu(userLoggedIn, allUniversities, allFavourites);
				break;

			case 3:
				displaySavedUniversities(userLoggedIn, allFavourites);
				break;

			case 4:
				displayFeedback(userLoggedIn, allUsers, allFeedbacks);
				break;

			case 5:
				displayFeedbackReplies(userLoggedIn);
				break;

			case 6:
				editUserProfile(userLoggedIn, allUsers);
				break;

			case 7:
				break;

			default:
				cout << "Please choose a valid option!" << endl;
				system("pause");
				userInterface(userLoggedIn, allUsers, allUniversities, allFeedbacks, allFavourites);
				break;

		}
	}
}

void displayUniversityDetails(User* userLoggedIn, LinkedList<University>* allUniversities, LinkedList<Favourite>* allFavourites) {
	// before displaying uni details the users can select whether to sort the universities by what field in ascending or descending order
	system("cls");
	systemHeading();

	LinkedList<University>* sortedUniversities = allUniversities->cloneLinkedList();
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

			return displayUniversityDetails(userLoggedIn, allUniversities, allFavourites);
		}

		// sort the cloned linked list
		sortedUniversities->setFirstNode(
			sortUniversities(
				sortedUniversities->getFirstNode(),
				&sortFieldType,
				&sortField,
				false // descending order
			)
		);

		displayUniversityRecords(userLoggedIn, sortedUniversities, allFavourites);

	}
	else if (sortSelection == 2) {
		// unsorted uni list
		displayUniversityRecords(userLoggedIn, sortedUniversities, allFavourites);

	}
	else {
		// recursively call this function until the input is valid
		cout << "Invalid input!" << endl;
		system("pause");

		return displayUniversityDetails(userLoggedIn, allUniversities, allFavourites);

	}

}

void displayUniversityRecords(User* userLoggedIn, LinkedList<University>* uniList, LinkedList<Favourite>* allFavourites) {
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
		if (currentNode->getNextAddress() == NULL) {
			cout << "1. Previous" << endl;
			cout << "2. Save as favourite." << endl;
			cout << "3. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			switch (selection) {
				case 1:
					currentNode = currentNode->getPreviousAddress();
					break;

				case 2:
					// save university as favourite
					saveUniversityAsFavourite(
						userLoggedIn,
						new Favourite(
							generateFavouriteId(allFavourites),
							userLoggedIn->getUserId(),
							currentNode->getData()->getInstitution()
						),
						allFavourites
					);
					break;

				case 3:
					return;

				default:
					cout << "Invalid input!" << endl;
					system("pause");

					break;
			}
		}
		else if (currentNode->getPreviousAddress() == NULL) {
			cout << "1. Next" << endl;
			cout << "2. Save as favourite." << endl;
			cout << "3. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			switch (selection) {
				case 1:
					currentNode = currentNode->getNextAddress();
					break;

				case 2:
					// save university as favourite
					saveUniversityAsFavourite(
						userLoggedIn,
						new Favourite(
							generateFavouriteId(allFavourites),
							userLoggedIn->getUserId(),
							currentNode->getData()->getInstitution()
						),
						allFavourites
					);
					break;

				case 3:
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
			cout << "3. Save as favourite." << endl;
			cout << "4. Quit" << endl;
			cout << "Enter your selection here --> ";
			cin >> selection;

			switch (selection) {
				case 1:
					currentNode = currentNode->getPreviousAddress();
					break;

				case 2:
					currentNode = currentNode->getNextAddress();
					break;

				case 3:
					// save university as favourite
					saveUniversityAsFavourite(
						userLoggedIn,
						new Favourite(
							generateFavouriteId(allFavourites),
							userLoggedIn->getUserId(),
							currentNode->getData()->getInstitution()
						),
						allFavourites
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

		// clear string elements in input stream
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
}

void searchUniversityMenu(User* userLoggedIn, LinkedList<University>* allUniversities, LinkedList<Favourite>* allFavourites) {
	// search university menu
	// ask users which field to search before searching
	// only returns 1 result and call printDetails to print its details.

	int action = 0;
	LinkedList<University>* sortedUniversities = allUniversities->cloneLinkedList();
	while (action != 3) {
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

				return searchUniversityMenu(userLoggedIn, allUniversities, allFavourites);
			}
		}
		else if (sortFieldType == "uni_rank") {
			bool validDigit = validateInteger(searchTarget);

			if (!validDigit) {
				cout << "The search value for rank is not valid! Please retry!" << endl;
				system("pause");

				return searchUniversityMenu(userLoggedIn, allUniversities, allFavourites);
			}
		}
		else if (sortFieldType == "score") {
			bool validDouble = validateDouble(searchTarget);

			if (!validDouble) {
				cout << "The search value for score is not valid! Please retry!" << endl;
				system("pause");

				return searchUniversityMenu(userLoggedIn, allUniversities, allFavourites);
			}
		}

		// sort the array according to the search field as binary search is implemented
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

		action = promptAction(userLoggedIn, universityFound, allFavourites);

	}
}

int promptAction(User* userLoggedIn, Node<University>* universityFound, LinkedList<Favourite>* allFavourites) {
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
						generateFavouriteId(allFavourites), // new id
						userLoggedIn->getUserId(),
						universityFound->getData()->getInstitution()
					),
					allFavourites
				);
				return 1;

			case 2:
				return 2;

			case 3:
				return 3;

			default:
				cout << "Invalid input!" << endl;
				system("pause");

				return promptAction(userLoggedIn, universityFound, allFavourites);
		}
	}
}

void saveUniversityAsFavourite(User* userLoggedIn, Favourite* favouriteUniversity, LinkedList<Favourite>* allFavourites) {
	// confirm want to save then proceed
	int confirmSave = 0;
	cout << "Do you really want to save the university \"" << favouriteUniversity->getFavouriteUniversity() << "\" as favourite university? (1 - Yes, 2 - No) >> ";
	cin >> confirmSave;

	switch (confirmSave) {
		case 1: {
			// save as favourite here
			Node<Favourite>* currentNode = userLoggedIn->getFavouriteUniversities()->getFirstNode();
			while (currentNode != NULL) {
				// linear search to find if this record already exists

				Favourite* favUni = currentNode->getData();
				if (favUni->getFavouriteUniversity() == favouriteUniversity->getFavouriteUniversity()) {
					// if found record then return with appropriate message
					cout << "This university is already saved by the users!" << endl;
					system("pause");

					return;
				}

				currentNode = currentNode->getNextAddress();
			}

			userLoggedIn->getFavouriteUniversities()->appendNewNode(favouriteUniversity);
			allFavourites->appendNewNode(favouriteUniversity);
			cout << "The university has been successfully saved!" << endl;
			system("pause");
			break;
		}
		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");

			return saveUniversityAsFavourite(userLoggedIn, favouriteUniversity, allFavourites);
	}
}

void displaySavedUniversities(User* userLoggedIn, LinkedList<Favourite>* allFavourites) {
	// display all favourite universities of that users
	system("cls");
	systemHeading();

	// user's favourite list
	LinkedList<Favourite>* favList = userLoggedIn->getFavouriteUniversities();
	
	// print the favourite university out
	Node<Favourite>* currentNode = favList->getFirstNode();

	cout << "Favourite List: " << endl << endl;
	while (currentNode != NULL) {

		cout << "Favourite Id: " << currentNode->getData()->getFavouriteId() << endl;
		cout << "University Name: " << currentNode->getData()->getFavouriteUniversity() << endl;
		if (currentNode->getNextAddress() != NULL)
			cout << string(50, '=') << endl;
		else
			cout << endl;

		currentNode = currentNode->getNextAddress();
	}

	int selection = 0;
	cout << "Do you wish to delete any favourite university saved?" << endl;
	cout << "1. Yes" << endl;
	cout << "2. No (will quit to user main menu)" << endl;
	cout << "Enter your selection >> ";
	cin >> selection;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	if (selection == 1) {
		// come back to this favourite interface after deleting saved uni
		deleteFavouriteUniversity(userLoggedIn, allFavourites);

		// travel back to this interface
		displaySavedUniversities(userLoggedIn, allFavourites);

	}
	else if (selection == 2) {
		return;

	}
	else {
		// return back to this menu after printing error message
		cout << "Invalid input from users! Please choose valid choice." << endl;
		system("pause");

		displaySavedUniversities(userLoggedIn, allFavourites);

	}
}

void deleteFavouriteUniversity(User* userLoggedIn, LinkedList<Favourite>* allFavourites) {
	int feedbackIdToDelete;
	cout << "Please enter the favourite id of the university saved you wish to delete >> ";
	cin >> feedbackIdToDelete;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Node<Favourite>* deleteFavFromAll = searchFavourite(allFavourites, feedbackIdToDelete);
	Node<Favourite>* deleteFavFromUser = searchFavourite(userLoggedIn->getFavouriteUniversities(), feedbackIdToDelete);

	if (deleteFavFromAll == NULL || deleteFavFromUser == NULL) {
		cout << "The saved university is not found!" << endl;
		system("pause");
	}
	else {
		// disconnect the targeted node from the linked list
		userLoggedIn->getFavouriteUniversities()->deleteThisNode(deleteFavFromUser); // delete from user's fav list
		allFavourites->deleteThisNode(deleteFavFromAll); // delete from all fav list

		cout << "The saved university has been deleted!" << endl;
		system("pause");
	}
}

void displayFeedback(User* userLoggedIn, LinkedList<User>* allUsers, LinkedList<Feedback>* allFeedbacks) {
	// show all the feedbacks sent, then give options to create 1
	system("cls");
	systemHeading();

	// get user's feedbacdisplayFeedbackks sent
	LinkedList<Feedback>* userFeedbacks = userLoggedIn->getFeedbackSent();
	Node<Feedback>* currentNode = userFeedbacks->getFirstNode();
	int counter = 1;
	
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
			sendFeedback(userLoggedIn, allUsers, allFeedbacks);
			break;

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			break;
	}
}

void sendFeedback(User* userLoggedIn, LinkedList<User>* allUsers, LinkedList<Feedback>* allFeedbacks) {
	// add a newly created feedback object to the feedback list
	system("cls");
	systemHeading();

	string content;
	cout << "Enter your feedback message here: ";
	getline(cin, content, '\n');

	// get admin's id
	User* admin = filterUsersByRole(allUsers, ADMIN)->getFirstNode()->getData();
	Feedback* feedbackSent = new Feedback(
		generateFeedbackId(allFeedbacks),
		userLoggedIn->getUserId(),
		admin->getUserId(),
		"User Feedback",
		content
	);

	// update the global feedback list data structure and user's object filtered list
	allFeedbacks->appendNewNode(feedbackSent);
	userLoggedIn->getFeedbackSent()->appendNewNode(feedbackSent);

	cout << "Feedback sent successfully!" << endl;
	system("pause");
}

void displayFeedbackReplies(User* userLoggedIn) {
	// display feedback replies by the admin based on the latest date
	system("cls");
	systemHeading();
	cout << "Feedback Replies from Admin: " << endl << endl;

	// sort feedback replies from the admin (descending)
	LinkedList<Feedback>* feedbacks = userLoggedIn->getFeedbackReplies();
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
}

void editUserProfile(User* userLoggedIn, LinkedList<User>* allUsers) {
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

			bool isUniqueRecord = checkRecordUniqueness(allUsers, userLoggedIn->getUserId(), &newUsername, &newEmail, &newPhone);
			if (!isUniqueRecord) {
				system("pause");
				return editUserProfile(userLoggedIn, allUsers);
			}

			// update immediately
			userLoggedIn->setUsername(newUsername);
			userLoggedIn->setPassword(newPassword);
			userLoggedIn->setEmail(newEmail);
			userLoggedIn->setPhone(newPhone);

			cout << "User profile is edited successfully!" << endl;
			system("pause");
			
			break;
		}

		case 2:
			return;

		default:
			cout << "Invalid input!" << endl;
			system("pause");
			return editUserProfile(userLoggedIn, allUsers);
	}
}
