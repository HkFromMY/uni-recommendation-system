#include "util.h"

int convertToInt(string str) {
	try {
		if (str != "") return stoi(str);
		else return NULL;
	}
	catch (...) {
		cout << "Error Integer String --> " << str << "end here" << endl;
	}
	
}

double convertToDouble(string str) {
	try {
		if (str == "-") return NULL;
		else if (str != "") return stod(str);
		else return NULL;
	}
	catch (...) {
		cout << "Error Double String --> " << str << "end here" << endl;
	}
}

string trimString(string value) {
	// this function trim leading and trailing string
	// src: https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
	const string WHITESPACE = " \n\r\t\f\v";
	string trimmed = value;

	// trim left side
	size_t start = value.find_first_not_of(WHITESPACE);
	if (start == string::npos) {
		trimmed = "";
	}
	else {
		trimmed = value.substr(start);
	}

	// trim right side
	size_t end = trimmed.find_last_not_of(WHITESPACE);
	if (end == string::npos) {
		trimmed = "";
	}
	else {
		trimmed = trimmed.substr(0, end + 1);
	}

	return trimmed;
}

// file functions
void writeToFile(string filepath, string content) {
	// receives content of string and overwrite the entire file given the filepath

	// output file stream
	ofstream output_stream(filepath);

	output_stream << content;

	output_stream.close();
}

void appendToFile(string filepath, string line) {
	// receives line of string and append to the end of file given the filepath
	ofstream output_stream(filepath, ios_base::app);

	if (output_stream.is_open()) {
		output_stream << line;
	}
	else {
		cerr << "ERROR: File not found!" << endl;
	}

	output_stream.close();
}
