#include "input_validation.h"

bool validateEmail(string email) {
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");

	return regex_match(email, pattern);
}

bool validatePhone(string phone) {
	// only check length, ASSUMES that the phone format provided is correct

	return phone.length() >= 10 && phone.length() <= 11;
}
