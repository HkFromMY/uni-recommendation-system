#include "university_model.h"

LinkedList<University>* loadUniversitiesData() {
	// This functions packs all data in CSV and return LinkedList's pointer

	LinkedList<University>* uni_list = new LinkedList<University>();

	string rank, ar_rank, er_rank, fsr_rank, cpf_rank, ifr_rank, isr_rank, irn_rank, ger_rank;
	string institution, location_code, location;
	string ar_score, er_score, fsr_score, cpf_score, ifr_score, isr_score, irn_score, ger_score, score_scaled;

	ifstream file("2023 QS World University Rankings.csv");

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
			new Rank(ar_rank), convertToDouble(er_score), new Rank(er_rank), convertToDouble(fsr_score), new Rank(fsr_rank), convertToDouble(cpf_score),
			new Rank(cpf_rank), convertToDouble(ifr_score), new Rank(ifr_rank), convertToDouble(isr_score), new Rank(isr_rank), convertToDouble(irn_score),
			new Rank(irn_rank), convertToDouble(ger_score), new Rank(ger_rank), convertToDouble(score_scaled)
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

// merge sort for universities
Node<University>* sortUniversities(Node<University>* node, string* sortFieldType, string* sortField, bool isAscending) {
	if (node == NULL || node->getNextAddress() == NULL) {
		return node;
	}

	Node<University>* secondHalf = splitUniversities(node);

	// recursively sorted for first and second halves of the sub-linkedlist
	node = sortUniversities(node, sortFieldType, sortField, isAscending);
	secondHalf = sortUniversities(secondHalf, sortFieldType, sortField, isAscending);

	// merge sorted sub-linkedlist
	return mergeUniversities(node, secondHalf, sortFieldType, sortField, isAscending);
}

Node<University>* splitUniversities(Node<University>* headNode) {
	Node<University>* currentNode = headNode;
	Node<University>* nextNode = headNode;

	while (nextNode->getNextAddress() && nextNode->getNextAddress()->getNextAddress()) {
		nextNode = nextNode->getNextAddress()->getNextAddress();
		currentNode = currentNode->getNextAddress();
	}

	Node<University>* temp = currentNode->getNextAddress();
	currentNode->setNextAddress(NULL);

	return temp;
}

Node<University>* mergeUniversities(
	Node<University>* firstHalf, 
	Node<University>* secondHalf, 
	string* sortFieldType, 
	string* sortField, 
	bool isAscending
) {
	if (firstHalf == NULL) return secondHalf;
	if (secondHalf == NULL) return firstHalf;

	// pick smaller values
	University* firstUniversity = firstHalf->getData();
	University* secondUniversity = secondHalf->getData();
	bool comparisonResult = compareValue(firstUniversity, secondUniversity, sortFieldType, sortField, isAscending);

	if (comparisonResult) {
		firstHalf->setNextAddress(mergeUniversities(firstHalf->getNextAddress(), secondHalf, sortFieldType, sortField, isAscending));
		firstHalf->getNextAddress()->setPreviousAddress(firstHalf);
		firstHalf->setPreviousAddress(NULL);

		return firstHalf;
	}
	else {
		secondHalf->setNextAddress(mergeUniversities(firstHalf, secondHalf->getNextAddress(), sortFieldType, sortField, isAscending));
		secondHalf->getNextAddress()->setPreviousAddress(secondHalf);
		secondHalf->setPreviousAddress(NULL);

		return secondHalf;
	}
}

bool compareValue(University* firstUniversity, University* secondUniversity, string* sortFieldType, string* sortField, bool isAscending) {
	// this functions accepts parameters and compare different types of data accordingly
	// returns a boolean 
	if (*sortFieldType == "uni_rank") {
		int value1 = firstUniversity->getRank();
		int value2 = secondUniversity->getRank();

		if (isAscending) return value1 < value2;
		else return value1 > value2;

	}
	else if (*sortFieldType == "text") {
		string value1 = firstUniversity->getStringValue(*sortField);
		string value2 = secondUniversity->getStringValue(*sortField);

		if (isAscending) return value1 < value2;
		else return value1 > value2;

	}
	else if (*sortFieldType == "score") {
		double value1 = firstUniversity->getScoreValue(*sortField);
		double value2 = secondUniversity->getScoreValue(*sortField);

		if (isAscending) return value1 < value2;
		else return value1 > value2;
	}
	else if (*sortFieldType == "rank_obj") {
		Rank* rank1 = firstUniversity->getRankValue(*sortField);
		Rank* rank2 = secondUniversity->getRankValue(*sortField);

		if (isAscending) return rank1->isHigherThan(rank2);
		else return rank1->isLowerThan(rank2);

	}
}