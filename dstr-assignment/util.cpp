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
