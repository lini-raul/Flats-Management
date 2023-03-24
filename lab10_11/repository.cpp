#include "repository.h"
#include "exceptions.h"
#include <fstream>
#include <sstream>

using std::find_if;
using std::remove_if;
//using std::erase;
using std::remove;
using std::ifstream;
using std::ofstream;
using std::stringstream;
using std::endl;

void RepoLocatari::add(const Locatar& loc)
{
	/*  pt VectDin
	for (const Locatar& l : locatari)
	{
		if(&l!=nullptr)
		if (l.getApartament() == loc.getApartament())
		{
			throw RepoException("Apartament deja existent!");
		}
	}
	locatari.push_back(loc);
	*/
	if (find_if(locatari.begin(), locatari.end(), [&loc](const Locatar& l) noexcept { return l.getApartament() == loc.getApartament(); }) == locatari.end())
		locatari.push_back(loc);
	else
		throw RepoException("Apartament deja existent!");
}

void RepoLocatari::modify(const int& ap, const string& nume, const double& suprafata, const string& tip)
{
	/*pt VectDin
	for (auto& l : locatari)
		if(&l!=nullptr)
		if (l.getApartament() == ap)
		{
			l.setNume(nume);
			l.setSuprafata(suprafata);
			l.setTip(tip);
		}
	*/
	auto it = find_if(locatari.begin(), locatari.end(), [&ap](const Locatar& l) noexcept { return l.getApartament() == ap; });
	//if(it->setNume() != nullptr)
	it->setNume(nume);
	it->setSuprafata(suprafata);
	it->setTip(tip);



}
void RepoLocatari::sterge(const int& ap) {
	/* pt VectDin
	for (IteratorVector i = locatari.begin(); i != locatari.end(); ++i)
		if ((*i).getApartament() == ap)
		{
			locatari.erase(i.get_poz());
			break;
		}
	*/

	auto it = remove_if(locatari.begin(), locatari.end(), [&ap](const Locatar& l) noexcept { return l.getApartament() == ap; });
	locatari.pop_back();

	//auto it = find_if(locatari.begin(), locatari.end(), [&ap](const Locatar& l) { return l.getApartament() == ap; });
	//remove(locatari.begin(), locatari.end(), *it);

}

//VectDin<Locatar> RepoLocatari::get_all() {  pt VectDin
vector<Locatar> RepoLocatari::get_all() {
	return locatari;
}

bool RepoLocatari::gasit(const int& ap) {
	/*
	try {
		find_after_apartment(ap);
		return true;
	}
	catch (RepoException&) {
		return false;
	}
	*/
	if (find_if(locatari.begin(), locatari.end(), [&ap](const Locatar& l) noexcept { return l.getApartament() == ap; }) == locatari.end())
		return false;
	return true;
}

const Locatar& RepoLocatari::find_after_apartment(const int ap) {

	for (const auto& l : locatari)
		if (&l != nullptr)
			if (l.getApartament() == ap)
				return l;
	throw RepoException("Apartament inexistent!");
}

void RepoLocatariFile::loadFromFile()
{
	ifstream locFile(this->filename);
	if (!locFile.is_open())
		throw RepoException("Nu se poate citi din fisier!");

	string line;
	while (getline(locFile, line))
	{
		string nume, tip;
		int ap;
		double suprf;

		stringstream linestream(line);
		string current;
		int nr = 0;
		while (getline(linestream, current, ','))
		{
			if (nr == 0) ap = stoi(current);
			if (nr == 1) nume = current;
			if (nr == 2) suprf = stod(current);
			if (nr == 3) tip = current;
			nr++;
		}

		Locatar loc{ ap, nume, suprf, tip };
		RepoLocatari::add(loc);
		//this->add(loc);
	}
	locFile.close();
}

void RepoLocatariFile::saveToFile()
{
	ofstream locFile(this->filename);
	if (!locFile.is_open())
		throw RepoException("Nu se poate scrie in fisier!");
	for (auto& loc : get_all())
	{
		locFile << loc.getApartament() << "," << loc.getNume() << "," << loc.getSuprafata() << "," << loc.getTip() << "\n";
	}
	locFile.close();
}

void RepoLocatariFile::add(const Locatar& loc)
{
	RepoLocatari::add(loc);
	saveToFile();
}

void RepoLocatariFile::modify(const int& ap, const string& nume, const double& suprafata, const string& tip)
{
	RepoLocatari::modify(ap, nume, suprafata, tip);
	saveToFile();
}

void RepoLocatariFile::sterge(const int& ap)
{
	RepoLocatari::sterge(ap);
	saveToFile();
}

