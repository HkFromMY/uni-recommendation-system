#include "Favourite.h"

Favourite::Favourite(int newFavouriteId, int newUserId, string newFavouriteUniversity) {
	favourite_id = newFavouriteId;
	user_id = newUserId;
	favourite_university = newFavouriteUniversity; 
}

Favourite::~Favourite() {}

int Favourite::getFavouriteId() { return favourite_id; }
int Favourite::getUserId() { return user_id; }
string Favourite::getFavouriteUniversity() { return favourite_university; }

void Favourite::setFavouriteId(int newFavouriteId) { favourite_id = newFavouriteId; }
void Favourite::setUserId(int newUserId) { user_id = newUserId; }
void Favourite::setFavouriteUniversity(string newFavouriteUniversity) { favourite_university = newFavouriteUniversity; }

void Favourite::printDetails() {
	cout << "Favourite Id: " << favourite_id << endl;
	cout << "User Id: " << user_id << endl;
	cout << "Favourite University: " << favourite_university << endl;
}

string Favourite::toString() {
	// returns object's details in string that represent a row in the favourites.txt
	string output_text = to_string(favourite_id) + "|" + to_string(user_id) + "|" + favourite_university + "\n";

	return output_text;
}
