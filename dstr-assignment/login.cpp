#include "login.h"
#include "common_interface.h"

void loginInterface() {
	system("cls");

	string username, password;

	systemHeading();
	cout << "Please enter your username >> ";
	getline(cin, username);

	cout << "Please enter your password >> ";
	getline(cin, password);

	// validate and verify password here
	bool credentialMatched = validateCredentials(username, password);
	if (credentialMatched) {
		// go other interface
		cout << "Login successfully!" << endl;
	}
	else {
		cout << "The credentials is incorrect!" << endl;

		bool wantLogin = promptLogin();
		if (wantLogin) {
			// if they want to try logging in again, then call loginInterface() again
			loginInterface();
		}
	}
}

bool validateCredentials(string username, string password) {
	LinkedList<User>* user_list = loadUserData("user.txt");
	
	Node<User>* currentUserNode = user_list->getFirstNode();
	while (currentUserNode != NULL) {
		// linear search O(N)
		User* user = currentUserNode->getData();
		if (user->isPasswordMatch(username, password)) {
			// if credentials matched
			cout << "Credentials Matched!" << endl;

			return true;
		}

		currentUserNode = currentUserNode->getNextAddress();
	}

	return false;
}

LinkedList<User>* loadUserData(string filepath) {
	LinkedList<User>* user_list = new LinkedList<User>();
	string username, password, role;
	ifstream file(filepath);

	if (!file.is_open()) {
		cerr << "ERROR: File Open" << endl;

		throw exception();
	}


	while (file.good()) {
		// get line by line
		getline(file, username, '|');
		getline(file, password, '|');
		getline(file, role, '\n');

		User* user = new User(
			username,
			password,
			role
		);

		user_list->appendNewNode(user);
	}

	return user_list;
}

bool promptLogin() {
	int relogin;
	cout << "Do you want to login again? (0 - No, 1 - Yes) >> ";
	cin >> relogin;

	// clear input stream and remaining elements
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
	if (relogin < 0 || relogin > 2) {
		// invalid options, then re-prompt
		return promptLogin();
	}

	// if user insert 1 then means they want login so this expression returns true
	return relogin == 1; 
}
