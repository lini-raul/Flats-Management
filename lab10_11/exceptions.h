#pragma once
#include <string>
#include <ostream>
using std::string;
using std::ostream;

class RepoException {
private:
	string msg;
public:
	RepoException(const string m);
	string getMessage() const;
	friend ostream& operator<<(ostream& out, const RepoException& ex);

};

ostream& operator<<(ostream& out, const RepoException& ex);
