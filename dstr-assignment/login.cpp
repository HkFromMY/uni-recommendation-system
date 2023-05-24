#include "login.h"
#include "common_interface.h"
#include "admin.h"
#include "util.h"
#include "UserMenu.h"

void loginInterface(
	LinkedList<User>* userList,
	LinkedList<University>* allUniversities,
	LinkedList<Feedback>* allFeedbacks,
	LinkedList<Favourite>* allFavourites
) {
	system("cls");
	systemHeading();

	string username, password;
	cout << "Please enter your username >> ";
	getline(cin, username);

	cout << "Please enter your password >> ";
	getline(cin, password);

	// validate and verify password here
	User* userFound = validateCredentials(userList, username, password);

	if (userFound == nullptr) {
		// if incorrect credentials
		cout << "The credentials is incorrect!" << endl;

		bool wantLogin = promptLogin();
		if (wantLogin) {
			// if they want to try logging in again, then call loginInterface() again
			loginInterface(
				userList,
				allUniversities,
				allFeedbacks,
				allFavourites
			);
		}
	}
	else {
		int login_role = userFound->getRole();
		userFound->setLastLoginDate(new Date());
		userFound->setFeedbackReplies(filterFeedbacksByRecipientId(allFeedbacks, userFound->getUserId())); // get all feedback replies from the admin
		userFound->setFeedbackSent(filterFeedbacksBySenderId(allFeedbacks, userFound->getUserId())); // get all feedback sent by this user
		userFound->setFavouriteUniversities(filterFavouriteByUser(allFavourites, userFound->getUserId())); // get all saved universities of this user

		// go other interface because correct credentials
		if (login_role == USER) {
			// registered user interface
			userInterface(userFound, userList, allUniversities, allFeedbacks, allFavourites);

		}
		else if (login_role == ADMIN) {
			// admin interface
			adminInterface(userFound, userList, allUniversities, allFeedbacks, allFavourites);

		}
	}
}

User* validateCredentials(LinkedList<User>* userList, string username, string password) {
	// search whether there is matched record in user record
	
	Node<User>* currentUserNode = userList->getFirstNode();
	while (currentUserNode != NULL) {
		// linear search O(N)
		User* user = currentUserNode->getData();

		if (user->isPasswordMatch(username, password)) {
			// if credentials matched

			return user;
		}

		currentUserNode = currentUserNode->getNextAddress();
	}

	return nullptr;
}

bool promptLogin() {
	// this function prompts the user whether they want to login or not
	// repeat until the users give valid input

	int relogin;
	cout << "Do you want to login again? (1 - Yes, 2 - No) >> ";
	cin >> relogin;

	// clear input stream and remaining elements
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	if (relogin <= 0 || relogin > 2) {
		// invalid options, then re-prompt
		system("cls");
		systemHeading();

		return promptLogin();
	}

	// if user insert 1 then means they want login so this expression returns true
	return relogin == 1; 
}
