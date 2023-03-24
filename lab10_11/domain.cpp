#include "domain.h"
#include <iostream>
using std::cout;

int Locatar::getApartament() const noexcept {
	return apartament;
}


string Locatar::getNume() const {
	return nume;
}

double Locatar::getSuprafata() const noexcept {
	return suprafata;
}

string Locatar::getTip() const
{
	return tip;
}

void Locatar::setNume(string nume)
{
	this->nume = nume;
}

void Locatar::setSuprafata(double suprafata) noexcept
{
	this->suprafata = suprafata;
}

void Locatar::setTip(string tip)
{
	this->tip = tip;
}

Locatar::Locatar(const int apartament, const string nume, const double suprafata, const string tip) : apartament{ apartament }, nume{ nume }, suprafata{ suprafata }, tip{ tip }{}

Locatar::Locatar(const Locatar& ot) : apartament{ ot.getApartament() }, nume{ ot.getNume() }, suprafata{ ot.getSuprafata() }, tip{ ot.getTip() } {
	//cout << "copy called\n";
}

bool Locatar::operator==(const Locatar& ot)
{
	if (this->getApartament() != ot.getApartament()) return false;
	if (this->getNume() != ot.getNume()) return false;
	if (this->getSuprafata() != ot.getSuprafata()) return false;
	if (this->getTip() != ot.getTip()) return false;

	return true;
}

bool cmpNume(const Locatar& l1, const Locatar& l2) {

	return l1.getNume() < l2.getNume();
}

bool cmpSuprafata(const Locatar& l1, const Locatar& l2) noexcept {

	return l1.getSuprafata() < l2.getSuprafata();
}

bool cmpTipSuprafata(const Locatar& l1, const Locatar& l2) {

	if (l1.getTip() == l2.getTip())
		return l1.getSuprafata() < l2.getSuprafata();
	else
		return l1.getTip() < l2.getTip();
}