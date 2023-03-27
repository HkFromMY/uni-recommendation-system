#include "Date.h"

bool isLeapYear(int year) {
	// source: https://www.geeksforgeeks.org/program-check-date-valid-not/
	if (
		((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)
	)
		return true;

	return false;
}

bool isValidDate(int newYear, int newMonth, int newDay) {
	if (
		(newYear < 1900 || newYear > 2500) ||
		(newMonth < 1 || newMonth > 12) ||
		(newDay < 1 || newDay > 31) ||
		((newMonth == 2) && (isLeapYear(newYear)) && (newDay > 29)) || // leap year but have over 29 days
		((newMonth == 2) && (!isLeapYear(newYear)) && (newDay > 28)) // not leap year but have over 28 days
		) {
		// basic validation and leap year validation on february's day
		return false;
	}

	if ((newMonth == 1 || newMonth == 3 || newMonth == 5 || newMonth == 7 || newMonth == 8 || newMonth == 10 || newMonth == 12) && newDay == 30) {
		// if those months have 30 days then wrong
		return false;
	}

	if ((newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11) && newDay == 31) {
		// if those months have 31 days then wrong
		return false;
	}

	return true;
}

Date::Date(int newYear, int newMonth, int newDay) {
	if (!isValidDate(newYear, newMonth, newDay)) {
		throw invalid_argument("The date is invalid!");
	}

	year = newYear;
	month = newMonth;
	day = newDay;
}

Date::Date(string date_str) {
	// validations must be done outside this constructor
	stringstream ss(date_str);
	string newYear_str, newMonth_str, newDay_str;

	// parse them into variables
	getline(ss, newYear_str, '-');
	getline(ss, newMonth_str, '-');
	getline(ss, newDay_str, '\n');

	// cast them into integer type
	int newYear = stoi(newYear_str);
	int newMonth = stoi(newMonth_str);
	int newDay = stoi(newDay_str);

	// validations
	if (!isValidDate(newYear, newMonth, newDay)) {
		throw invalid_argument("The date is invalid!");
	}

	year = newYear;
	month = newMonth;
	day = newDay;
}

int Date::getYear() { return year; }
int Date::getMonth() { return month; }
int Date::getDay() { return day; }

void Date::setYear(int newYear) { year = newYear; }
void Date::setMonth(int newMonth) { month = newMonth; }
void Date::setDay(int newDay) { day = newDay; }

void Date::printDate() {
	cout << year << "-"
		<< setfill('0') << setw(2) << month << "-"
		<< setfill('0') << setw(2) << day << endl;
}

bool Date::isAfter(Date* date) {
	// check year first
	if (year > date->getYear()) return true;

	// check month then
	if (month > date->getMonth()) return true;

	// check day only
	if (day > date->getDay()) return true;
}

bool Date::isBefore(Date* date) {
	// check year first
	if (year < date->getYear()) return true;

	// check month then
	if (month < date->getMonth()) return true;

	// check day only
	if (day < date->getDay()) return true;
}

bool Date::isEqual(Date* date) {
	// check year first
	if (year == date->getYear()) return true;

	// check month then
	if (month == date->getMonth()) return true;

	// check day only
	if (day == date->getDay()) return true;
}


