#include "validatori.h"
#include <vector>
#include <string>
#include <sstream>

void LocatarValidator::validate(const Locatar& l)
{
	vector<string> msgs;
	if (l.getApartament() < 0) msgs.push_back("Apartament negativ!");
	if (l.getNume().size() == 0) msgs.push_back("Nume vid!");
	if (l.getSuprafata() < 0) msgs.push_back("Suprafata negativa!");
	if (l.getTip().size() == 0) msgs.push_back("Tip vid!");

	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		if (&msg != nullptr)
			out << msg << " ";
	}
	return out;
}

string ValidateException::getMessage() const
{
	string mesaj;
	for (const auto& i : msgs)
		mesaj += i;
	return mesaj;
}
