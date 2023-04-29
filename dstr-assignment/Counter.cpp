#include "Counter.h"

Counter::Counter(string key, int value) {
	this->key = key;
	this->value = value;
}

Counter::~Counter() {}

string Counter::getKey() { return key; }
int Counter::getValue() { return value; }

void Counter::setKey(string key) { this->key = key; }
void Counter::setValue(int value) { this->value = value; }

void Counter::printDetails() {
	cout << "Key: " << key << endl;
	cout << "Value: " << value << endl;
}
