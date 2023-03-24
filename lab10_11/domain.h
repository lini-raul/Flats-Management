#pragma once
#include <string>
using std::string;

class Locatar {
private:
	int apartament = 0;
	string nume;
	double suprafata = 0;
	string tip;
public:
	int getApartament() const noexcept;
	string getNume() const;
	double getSuprafata() const noexcept;
	string getTip() const;

	void setNume(string nume);
	void setSuprafata(double suprafata) noexcept;
	void setTip(string tip);

	//constructor
	Locatar() = default;
	Locatar(const int apartament, const string nume, const double suprafata, const string tip);
	Locatar(const Locatar&);
	bool operator==(const Locatar& ot);


};

bool cmpNume(const Locatar& l1, const Locatar& l2);
bool cmpSuprafata(const Locatar& l1, const Locatar& l2) noexcept;
bool cmpTipSuprafata(const Locatar& l1, const Locatar& l2);
