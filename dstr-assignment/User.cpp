#include "User.h"

User::User(
	string newUsername, 
	string newPassword, 
	string newEmail, 
	string newPhone, 
	string newRole
) {
	username = newUsername;
	password = newPassword;
	email = newEmail;
	phone = newPhone;
	role = newRole;

	// validations
	if (
		role != "user" &&
		role != "admin" &&
		role != "guest"
	) {
		throw invalid_argument("Invalid role for User class.");
	}
}

string User::getUsername() { return username; }
string User::getPassword() { return password; }
int User::getRole() {
	// return integer based on user object's role

	if (role == "user") {
		return USER;
	}
	else if (role == "admin") {
		return ADMIN;
	}

	return GUEST;
}
string User::getEmail() { return email; }
string User::getPhone() { return phone; }

void User::setUsername(string newUsername) { username = newUsername; }
void User::setPassword(string newPassword) { username = newPassword; }
void User::setEmail(string newEmail) { username = newEmail; }
void User::setPhone(string newPhone) { username = newPhone; }
void User::setRole(string newRole) { username = newRole; }

bool User::isPasswordMatch(string usernameEntered, string passwordEntered) {
	return (
		(username == usernameEntered) &&
		(password == passwordEntered)
	);
}

void User::printDetails() {
	cout << "Username: " << username << endl;
	cout << "Email: " << email << endl;
	cout << "Phone: " << phone << endl;
	cout << "Role: " << role << endl;
}

User::~User() {}