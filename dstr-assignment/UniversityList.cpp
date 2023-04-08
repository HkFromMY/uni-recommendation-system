#include "UniversityList.h"
#include "util.h"

UniversityList::UniversityList() {
	head = NULL;
	count = 0;
	last = NULL;
}

void UniversityList::appendNewNode(University* newUniversity) {
	// complexity O(1) as no loop involved

	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
		last = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);
	}
	else {
		// original last element's next address becomes new node's address
		last->setNextAddress(newNode);

		// new node's previous address set to original last element's address
		newNode->setPreviousAddress(last);

		// new last address becomes new node
		last = newNode;

	}

	count++;
	//cout << "New node appended to the end of linked list." << endl;
}

void UniversityList::insertNodeAt(University* newUniversity, int position) {
	// complexity O(N)

	// insert new node at 'position' argument given
	// this class use zero-based indexing so the first node has index 0

	UniversityNode* newNode = new UniversityNode(newUniversity);

	if (head == NULL) {
		head = newNode;
		last = newNode;
		newNode->setNextAddress(head);
		newNode->setPreviousAddress(head);

		return;
	}

	if (position > count - 1) {
		// append to the end of the linked list
		appendNewNode(newUniversity);

		return;
	}

	UniversityNode* currentNode = head;
	for (int currentIndex = 0; currentIndex <= position; currentIndex++) {

		if (currentIndex == position - 1) {
			// set the previous address of original node at n position to new node
			currentNode->getNextAddress()->setPreviousAddress(newNode);

			// set the next address of new node to original node at n position
			newNode->setNextAddress(currentNode->getNextAddress());

			// set next address of current node to the new node
			currentNode->setNextAddress(newNode);

			// put previous address of new node to current node
			newNode->setPreviousAddress(currentNode);

			cout << "Node has been inserted!" << endl;
			count++;
			break;
		}

		currentNode = currentNode->getNextAddress();
	}

}

void UniversityList::deleteNodeAtFront() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		
		return;
	}

	UniversityNode* nodeToBeDeleted = head;
	head = head->getNextAddress(); // set new head to next address of the original head

	if (head != NULL) {
		// if the linked list have 2 or more elements, then set the previous address of new head to NULL
		head->setPreviousAddress(NULL);

	}
	else {
		last = NULL;

	}

	delete nodeToBeDeleted;
}

void UniversityList::deleteNodeAtEnd() {
	// complexity O(1)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	UniversityNode* nodeToBeDeleted = last;
	last = last->getPreviousAddress();

	if (last != NULL) {
		last->setNextAddress(NULL);
	}
	else {
		head = NULL;
	}

	delete nodeToBeDeleted;
}

void UniversityList::deleteNodeAt(int position) {
	// complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		return;
	}

	if (position > count - 1) {
		throw out_of_range("Index out of range!");
	}

	UniversityNode* currentNode = head;
	UniversityNode* previousNode = currentNode->getPreviousAddress();

	for (int currentIndex = 0; currentIndex <= position; currentIndex++) {
		
		if (currentIndex == position) {
			// reconnect the previous address of next node and next address of previous node after deleting the node
			previousNode->setNextAddress(currentNode->getNextAddress());
			currentNode->getNextAddress()->setPreviousAddress(previousNode);

			if (currentNode == head) {
				// if currentNode is head, then reset the head also
				head = currentNode->getNextAddress();
			}

			delete currentNode;
			count--;
		}
		else {
			currentNode = currentNode->getNextAddress();
			previousNode = currentNode->getPreviousAddress();
		}
	}

}

void UniversityList::displayNodesDetailsFromFront() {
	// time complexity O(N)
	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;

		return;
	}

	// iterate through the linked list and print everything
	UniversityNode* currentNode = head;
	while (currentNode != NULL) {
		University* currentUni = currentNode->getData();

		cout << "Institution Name --> " << currentUni->getInstitution() << endl;
		cout << "AR Rank --> " << currentUni->getARRank() << endl;
		cout << "AR Score --> " << currentUni->getARScore() << endl;
		cout << "Score scaled --> " << currentUni->getScoreScaled() << endl;
		cout << string(50, '=') << endl;

		currentNode = currentNode->getNextAddress();
	}
}

void UniversityList::displayNodeDetailsFromEnd() {
	// time complexity O(N)

	if (head == NULL) {
		cout << "The Linked list is empty!" << endl;
		
		return;
	}

	// iterate through the linked lsit and print everything
	UniversityNode* currentNode = last;
	while (currentNode != NULL) {
		University* currentUni = currentNode->getData();

		cout << "Institution Name --> " << currentUni->getInstitution() << endl;
		cout << "AR Rank --> " << currentUni->getARRank() << endl;
		cout << "AR Score --> " << currentUni->getARScore() << endl;
		cout << "Score scaled --> " << currentUni->getScoreScaled() << endl;
		cout << string(50, '=') << endl;

		currentNode = currentNode->getPreviousAddress();
	}
}

// searching functions (returns one search results)
University* UniversityList::searchByText(string field, string target) {
	return new University(1, "asdasdasd");
}

University* UniversityList::searchByNumeric(string field, int target) {
	return new University(1, "asdasdasd");
}

// filtering functions (returns multiple search results)
UniversityList* UniversityList::filterName(string target) {
	return new UniversityList();
}

UniversityList* UniversityList::filterScore(double lower_range, double upper_range) {
	return new UniversityList();
}

UniversityList* UniversityList::filterRank(int lower_range, int upper_range) {
	return new UniversityList();
}

UniversityList* loadCSVFile(string filepath) {
	// This functions packs all data in CSV and return UniversityList's pointer

	UniversityList* uni_list =  new UniversityList();

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

UniversityList::~UniversityList() {}