#include "login.h"
#include "common_interface.h"

void loginInterface() {
	system("cls");

	string username, password;

	systemHeading();
	cout << "Please enter your username --> " << endl;
	getline(cin, username);

	cout << "Please enter your password --> " << endl;
	cin >> password;
	getline(cin, password);

	// validate and verify password here

}

void validateCredentials() {

}

void loadUserData() {

}
