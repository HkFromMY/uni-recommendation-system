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

LinkedList<University>* loadCSVFile(string filepath) {
	// This functions packs all data in CSV and return LinkedList's pointer

	LinkedList<University>* uni_list = new LinkedList<University>();

	string rank, ar_rank, er_rank, fsr_rank, cpf_rank, ifr_rank, isr_rank, irn_rank, ger_rank;
	string institution, location_code, location;
	string ar_score, er_score, fsr_score, cpf_score, ifr_score, isr_score, irn_score, ger_score, score_scaled;

	ifstream file(filepath);

	if (!file.is_open()) {
		cerr << "ERROR: File Open" << endl;

		throw exception();
	}

	string line, remaining_line;

	while (file.good()) {
		// get line by line
		getline(file, line, '\n');

		// create string stream with the line and declare new stringstream for the remaining_line
		stringstream line_stream(line);
		stringstream remaining_stream;

		// parse data
		getline(line_stream, rank, ',');
		getline(line_stream, remaining_line, '\n');

		if (remaining_line.front() == '"') {
			// extract institution out from the line
			institution = remaining_line.substr(1, remaining_line.find("\",") - 1);

			// offset by 3 is because the need to add back the 1 subtracted above and double quotes and commas
			remaining_line = remaining_line.substr(institution.size() + 3, remaining_line.size());

			// convert back to stringstream
			remaining_stream << remaining_line;
		}
		else {
			// convert back remaining line into string stream object
			remaining_stream.clear();
			remaining_stream.str(remaining_line);

			// parse the university name out of it
			getline(remaining_stream, institution, ',');

		}

		// skip first rows and last row (blank line)
		if (institution == "Institution") {
			continue;
		}
		else if (rank == "") {
			break;
		}

		getline(remaining_stream, location_code, ',');

		// parse location (same process as above)
		getline(remaining_stream, remaining_line, '\n');
		if (remaining_line.front() == '"') {

			// extract institution out from the line
			location = remaining_line.substr(1, remaining_line.find("\",") - 1);

			// offset by 3 is because the need to add back the 1 subtracted above and double quotes and commas
			remaining_line = remaining_line.substr(location.size() + 3, remaining_line.size());

			// convert back to stringstream
			remaining_stream << remaining_line;
		}
		else {
			// clear stream from previous loop
			remaining_stream.clear();
			remaining_stream.str(remaining_line);

			// parse the university name out of it
			getline(remaining_stream, location, ',');

		}

		getline(remaining_stream, ar_score, ',');
		getline(remaining_stream, ar_rank, ',');
		getline(remaining_stream, er_score, ',');
		getline(remaining_stream, er_rank, ',');
		getline(remaining_stream, fsr_score, ',');
		getline(remaining_stream, fsr_rank, ',');
		getline(remaining_stream, cpf_score, ',');
		getline(remaining_stream, cpf_rank, ',');
		getline(remaining_stream, ifr_score, ',');
		getline(remaining_stream, ifr_rank, ',');
		getline(remaining_stream, isr_score, ',');
		getline(remaining_stream, isr_rank, ',');
		getline(remaining_stream, irn_score, ',');
		getline(remaining_stream, irn_rank, ',');
		getline(remaining_stream, ger_score, ',');
		getline(remaining_stream, ger_rank, ',');
		getline(remaining_stream, score_scaled, '\n');

		// create University object
		University* uni = new University(
			convertToInt(rank), institution, location_code, location, convertToDouble(ar_score),
			convertToInt(ar_rank), convertToDouble(er_score), convertToInt(er_rank), convertToDouble(fsr_score), convertToInt(fsr_rank), convertToDouble(cpf_score),
			convertToInt(cpf_rank), convertToDouble(ifr_score), convertToInt(ifr_rank), convertToDouble(isr_score), convertToInt(isr_rank), convertToDouble(irn_score),
			convertToInt(irn_rank), convertToDouble(ger_score), convertToInt(ger_rank), convertToDouble(score_scaled)
		);

		// append new node to the linked list
		uni_list->appendNewNode(uni);

		// clean input stream after every loop
		remaining_stream.clear();
		remaining_stream.str("");
		line_stream.clear();
		line_stream.str("");

	}

	return uni_list;
}

LinkedList<User>* loadUserData(string filepath) {
	// load the user data from text file into LinkedList of User objects
	LinkedList<User>* user_list = new LinkedList<User>();
	string username, password, email, phone, role;
	ifstream file(filepath);

	if (!file.is_open()) {
		cerr << "ERROR: File Open" << endl;

		throw exception();
	}


	while (file.good()) {
		// get line by line
		getline(file, username, '|');
		getline(file, password, '|');
		getline(file, email, '|');
		getline(file, phone, '|');
		getline(file, role, '\n');

		if (username == "") {
			// ignore last row
			break;
		}

		User* user = new User(
			username,
			password,
			email,
			phone,
			role
		);

		user_list->appendNewNode(user);
	}

	return user_list;
}
