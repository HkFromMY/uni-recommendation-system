#include "User.h"

User::User(
	int newUserId,
	string newUsername, 
	string newPassword, 
	string newEmail, 
	string newPhone, 
	string newRole,
	Date* lastLoginDate
) {
	user_id = newUserId;
	username = newUsername;
	password = newPassword;
	email = newEmail;
	phone = newPhone;
	role = newRole;
	last_login_date = lastLoginDate;

	// validations
	if (
		role != "user" &&
		role != "admin" &&
		role != "guest"
	) {
		throw invalid_argument("Invalid role for User class.");
	}
}

int User::getUserId() { return user_id; }
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
Date* User::getLastLoginDate() { return last_login_date; }
bool User::isInactive() {
	Date* today = new Date();

	if (last_login_date->differenceBetweenTwoDates(today) > 90) {
		return true;
	}

	return false;
}

void User::setUserId(int newUserId) { user_id = newUserId; }
void User::setUsername(string newUsername) { username = newUsername; }
void User::setPassword(string newPassword) { password = newPassword; }
void User::setEmail(string newEmail) { email = newEmail; }
void User::setPhone(string newPhone) { phone = newPhone; }
void User::setRole(string newRole) { 
	if (
		role != "user" &&
		role != "admin"
	) {
		throw invalid_argument("Invalid user role!");
	}

	role = newRole; 
}
void User::setLastLoginDate(Date* newLastLoginDate) { last_login_date = newLastLoginDate; }

bool User::isPasswordMatch(string usernameEntered, string passwordEntered) {
	return (
		(username == usernameEntered) &&
		(password == passwordEntered)
	);
}

void User::printDetails() {
	cout << "User Id: " << user_id << endl;
	cout << "Username: " << username << endl;
	cout << "Email: " << email << endl;
	cout << "Phone: " << phone << endl;
	cout << "Role: " << role << endl;
	cout << "Last Login Date: " << last_login_date->toString() << endl;
}

string User::toString() {
	// convert user object to string represented in text file
	string output = to_string(user_id) + "|" + username + "|" + password + "|" + email + "|" + phone + "|" + role + "|" + last_login_date->toString() + "\n";

	return output;
}

User::~User() {}