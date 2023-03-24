#pragma once
#include "domain.h"
#include <string>
#include <vector>

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
	string getMessage() const;
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class LocatarValidator {
public:
	void validate(const Locatar& l);
};
