#include "Feedback.h"
#include "Date.h"

Feedback::Feedback(string user_id, string comment) {
	this->sender_id = user_id;
	this->comment = comment;
	this->send_date = new Date(); // current date as the send date
}

string Feedback::getSenderId() { return sender_id; }
string Feedback::getComment() { return comment; }
Date* Feedback::getSendDate() { return send_date; }

void Feedback::setSenderId(string new_user_id) { sender_id = new_user_id; }
void Feedback::setComment(string new_comment) { comment = new_comment; }
void Feedback::setSendDate(Date* new_send_date) { send_date = new_send_date; }

void Feedback::printDetails() {}

Feedback::~Feedback() {}