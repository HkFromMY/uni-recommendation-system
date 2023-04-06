#include "Feedback.h"

Feedback::Feedback(string user_id, string comment) {
	this->sender_id = user_id;
	this->comment = comment;
}

string Feedback::getSenderId() { return sender_id; }
string Feedback::getComment() { return comment; }

void Feedback::setSenderId(string new_user_id) { sender_id = new_user_id; }
void Feedback::setComment(string new_comment) { comment = new_comment; }

void Feedback::printDetails() {}

Feedback::~Feedback() {}