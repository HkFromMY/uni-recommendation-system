#include "User.h"

User::User(string newUsername, string newPassword, string newRole) {
	username = newUsername;
	password = newPassword;
	role = newRole;
}

string User::getUsername() { return username; }
string User::getPassword() { return password; }
string User::getRole() { return role; }

void User::setUsername(string newUsername) { username = newUsername; }
void User::setPassword(string newPassword) { username = newPassword; }
void User::setRole(string newRole) { username = newRole; }

void User::printDetails() {
	cout << "Username: " << username << endl;
	cout << "Password: " << password << endl;
}