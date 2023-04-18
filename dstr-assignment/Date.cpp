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
	// validate the date attributes
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

	if ((newMonth == 1 || newMonth == 3 || newMonth == 5 || newMonth == 7 || newMonth == 8 || newMonth == 10 || newMonth == 12) && newDay > 31) {
		// if those months have over 31 days then wrong
		return false;
	}

	if ((newMonth == 4 || newMonth == 6 || newMonth == 9 || newMonth == 11) && newDay > 30) {
		// if those months have over 30 days then wrong
		return false;
	}

	return true;
}

Date::Date() {
	// set current system date with default constructor
	
	// Get the current system time
	time_t now = time(nullptr);

	// Convert to local time using localtime_s
	tm time_info;
	localtime_s(&time_info, &now);

	// Extract the date components with UNIX timestamp
	int year = time_info.tm_year + 1900;   // years since 1900
	int month = time_info.tm_mon + 1;      // months since January (0-11)
	int day = time_info.tm_mday;           // day of the month (1-31)

	// set the date attributes
	this->year = year;
	this->month = month;
	this->day = day;
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
	getline(ss, newDay_str);

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

string Date::toString() {
	stringstream month_stream;
	month_stream << setw(2) << setfill('0') << month;
	string month = month_stream.str();

	stringstream day_stream;
	day_stream << setw(2) << setfill('0') << day;
	string day = day_stream.str();

	// YYYY-MM-DD format
	return to_string(year) + "-" + month + "-" + day;
}

bool Date::isAfter(Date* date) {
	// check year first
	if (year > date->getYear()) return true;

	// check month then
	if (month > date->getMonth()) return true;

	// check day only
	if (day > date->getDay()) return true;

	return false;
}

bool Date::isBefore(Date* date) {
	// check year first
	if (year < date->getYear()) return true;

	// check month then
	if (month < date->getMonth()) return true;

	// check day only
	if (day < date->getDay()) return true;

	return false;
}

bool Date::isEqual(Date* date) {
	// check year first
	if (
		year == date->getYear() && 
		month == date->getMonth() && 
		day == date->getDay()
	) 
		return true;

	return false;
}

int differenceSince1900(Date* date) {
	// helper functions to calculate the difference in days since 1st January, 1900

	// boolean value is 0 and 1 in C++
	int daysPerMonth[] = {
		31, 28 + isLeapYear(date->getYear()), 31,
		30, 31, 30,
		31, 31, 30,
		31, 30, 31
	};

	// calculate difference of the date since January 1, 1900
	int days = 0;
	for (int start_year = 1900; start_year < date->getYear(); start_year++) {
		days += 365 + isLeapYear(start_year); // 366 days if it's leap year
	}

	for (int start_month = 1; start_month < date->getMonth(); start_month++) {
		days += daysPerMonth[start_month - 1]; // offset array index by 1
	}

	days += date->getDay() - 1; // subtract 1 as we start counting from 0

	return days;
}

int Date::differenceBetweenTwoDates(Date* date) {
	int differenceSince1900_1 = differenceSince1900(this);
	int differenceSince1900_2 = differenceSince1900(date);

	int difference_in_days = abs(differenceSince1900_1 - differenceSince1900_2);

	return difference_in_days;
}

Date::~Date() {}

