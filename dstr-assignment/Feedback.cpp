#include "Feedback.h"

Feedback::Feedback(int newFeedbackId, int newUserId, int newRecipient, string newType, string newComment) {
	// for creating a new feedback
	feedback_id = newFeedbackId;
	sender_id = newUserId;
	recipient_id = newRecipient;
	type = newType;
	comment = newComment;
	send_date = new Date(); // current date as the send date
}

Feedback::Feedback(int newFeedbackId, int newUserId, int newRecipientId, string newType, string newComment, Date* newSendDate) {
	// for loading an existing feedback
	feedback_id = newFeedbackId;
	sender_id = newUserId;
	recipient_id = newRecipientId;
	type = newType;
	comment = newComment;
	send_date = newSendDate;
}

int Feedback::getFeedbackId() { return feedback_id; }
int Feedback::getSenderId() { return sender_id; }
int Feedback::getRecipientId() { return recipient_id; }
string Feedback::getType() { return type; }
string Feedback::getComment() { return comment; }
Date* Feedback::getSendDate() { return send_date; }

void Feedback::setFeedbackId(int newFeedbackId) { feedback_id = newFeedbackId; }
void Feedback::setSenderId(int newUserId) { sender_id = newUserId; }
void Feedback::setRecipientId(int newRecipientId) { recipient_id = newRecipientId; }
void Feedback::setType(string newType) { type = newType; }
void Feedback::setComment(string newComment) { comment = newComment; }
void Feedback::setSendDate(Date* newSendDate) { send_date = newSendDate; }

void Feedback::printDetails() {
	cout << "Feedback Id: " << to_string(feedback_id) << endl;
	cout << "Sender Id: " << to_string(sender_id) << endl;
	cout << "Recipient Id: " << to_string(recipient_id) << endl;
	cout << "Feedback Type: " << type << endl;
	cout << "Comment: " << comment << endl;
	cout << "Send Date: " << send_date->toString() << endl;
}

string Feedback::toString() {
	// convert feedback object to string represented in text file
	string output = to_string(feedback_id) + "|" + to_string(sender_id) + "|" + to_string(recipient_id) + "|" + type + "|" + comment + "|" + send_date->toString() + "\n";

	return output;
}

Feedback::~Feedback() {}