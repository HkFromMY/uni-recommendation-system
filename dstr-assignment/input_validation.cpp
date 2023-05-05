#include "input_validation.h"

bool validateEmail(string email) {
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return regex_match(email, pattern);
}

bool validatePhone(string phone) {
	// only check length, ASSUMES that the phone format provided is correct

	return phone.length() >= 10 && phone.length() <= 11;
}

bool validateRank(string rank) {
	const regex pattern("^[0-9]{1,3}\\+{0,1}$");
	
	return regex_match(rank, pattern);
}
