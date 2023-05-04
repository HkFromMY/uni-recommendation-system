#include "feedback_model.h"

Node<Feedback>* sortFeedbackByDate(Node<Feedback>* node) {
	if (node == NULL || node->getNextAddress() == NULL) {
		return node;
	}

	Node<Feedback>* secondHalf = splitFeedback(node);

	// recursively sorted for first and second halves of the sub-linkedlist
	node = sortFeedbackByDate(node);
	secondHalf = sortFeedbackByDate(secondHalf);

	// merge sorted sub-linkedlist
	return mergeFeedback(node, secondHalf);
}

Node<Feedback>* splitFeedback(Node<Feedback>* headNode) {
	Node<Feedback>* currentNode = headNode;
	Node<Feedback>* nextNode = headNode;

	while (nextNode->getNextAddress() && nextNode->getNextAddress()->getNextAddress()) {
		nextNode = nextNode->getNextAddress()->getNextAddress();
		currentNode = currentNode->getNextAddress();
	}

	Node<Feedback>* temp = currentNode->getNextAddress();
	currentNode->setNextAddress(NULL);

	return temp;
}

Node<Feedback>* mergeFeedback(Node<Feedback>* firstHalf, Node<Feedback>* secondHalf) {
	if (firstHalf == NULL) return secondHalf;
	if (secondHalf == NULL) return firstHalf;

	// pick smaller values
	Feedback* firstFeedback = firstHalf->getData();
	Feedback* secondFeedback = secondHalf->getData();

	if (firstFeedback->getSendDate()->isBefore(secondFeedback->getSendDate())) {
		firstHalf->setNextAddress(mergeFeedback(firstHalf->getNextAddress(), secondHalf));
		firstHalf->getNextAddress()->setPreviousAddress(firstHalf);
		firstHalf->setPreviousAddress(NULL);

		return firstHalf;
	}
	else {
		secondHalf->setNextAddress(mergeFeedback(firstHalf, secondHalf->getNextAddress()));
		secondHalf->getNextAddress()->setPreviousAddress(secondHalf);
		secondHalf->setPreviousAddress(NULL);

		return secondHalf;
	}

}

LinkedList<Feedback>* filterFeedbacksByType(LinkedList<Feedback>* feedbacks, string feedbackType) {
	// time complexity - O(N)
	LinkedList<Feedback>* filteredFeedbacks = new LinkedList<Feedback>();

	Node<Feedback>* currentNode = feedbacks->getFirstNode();
	while (currentNode != NULL) {
		if (currentNode->getData()->getType() == feedbackType) {
			filteredFeedbacks->appendNewNode(currentNode->getData());
		}

		currentNode = currentNode->getNextAddress();
	}

	return filteredFeedbacks;
}

LinkedList<Feedback>* loadFeedbackData() {
	// load the feedback data from text file into LinkedList of Feedback objects
	LinkedList<Feedback>* feedback_list = new LinkedList<Feedback>();
	string feedback_id, sender_id, recipient_id, type, comment, send_date;
	ifstream file("feedback.txt");

	if (!file.is_open()) {
		cerr << "ERROR: File not found!" << endl;

		throw exception();
	}

	// parsing data and return list of feedback records
	while (file.good()) {
		getline(file, feedback_id, '|');
		getline(file, sender_id, '|');
		getline(file, recipient_id, '|');
		getline(file, type, '|');
		getline(file, comment, '|');
		getline(file, send_date, '\n');

		if (feedback_id == "") {
			break;
		}

		Feedback* feedback = new Feedback(
			convertToInt(feedback_id),
			convertToInt(sender_id),
			convertToInt(recipient_id),
			type,
			comment,
			new Date(send_date)
		);

		feedback_list->appendNewNode(feedback);
	}

	return feedback_list;
}

int generateFeedbackId() {
	// this function generates new feedback id by incrementing to the latest feedback records by 1
	LinkedList<Feedback>* feedbackList = loadFeedbackData();
	Feedback* lastFeedback = feedbackList->getLastNode()->getData();

	return lastFeedback->getFeedbackId() + 1;
}

void appendNewFeedbackOnFile(Feedback* newFeedback) {
	if (newFeedback == NULL) {
		cout << "Feedback object cannot be NULL!";

		return;
	}

	// append to the feedback.txt file
	appendToFile("feedback.txt", newFeedback->toString());
}

string latestFeedbackRecordInString(LinkedList<Feedback>* latestFeedbacks) {
	// returns latest feedback objects in string that represents records in text file
	// time complexity - O(N)

	string outputText = "";
	Node<Feedback>* currentNode = latestFeedbacks->getFirstNode();

	while (currentNode != NULL) {
		outputText += currentNode->getData()->toString();

		currentNode = currentNode->getNextAddress();
	}

	return outputText;
}