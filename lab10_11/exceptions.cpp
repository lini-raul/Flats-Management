#include "exceptions.h"
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

RepoException::RepoException(const string m) :msg{ m } {}

string RepoException::getMessage() const {
	return this->msg;
}

ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}