#include "service.h"
#include "exceptions.h"
#include "domain.h"
//#include <map>
using std::copy_if;
using std::sort;
using std::back_inserter;
using std::pair;
using std::make_unique;

// VectDin<Locatar> SrvLocatari::get_all() {
const vector<Locatar> SrvLocatari::get_all() {
	return repo.get_all();
}

void SrvLocatari::addToListaNotif(const Locatar& loc)
{
	lista_notif_curenta.add(loc);
}

void SrvLocatari::addRandomToListaNotif(int nr)
{
	lista_notif_curenta.addRandom(repo.get_all(), nr);
}

void SrvLocatari::emptyListaNotif() noexcept
{
	lista_notif_curenta.empty();
}

const vector<Locatar>& SrvLocatari::get_allListaNotif() noexcept
{
	return lista_notif_curenta.get_all();
}

void SrvLocatari::undo()
{
	if (undoActions.empty())
		throw RepoException("Nu exista alte operatii!");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}

const map<double, int> SrvLocatari::raport_suprafata()
{
	map<double, int> dict;
	for (auto const& l : repo.get_all())
	{

		auto it = dict.find(l.getSuprafata());
		if (it == dict.end())
		{
			dict.insert(pair<double, int>(l.getSuprafata(), 1));
		}
		else
		{
			dict.at(l.getSuprafata())++;
		}
	}
	return dict;
}


void SrvLocatari::add(const int& ap, const string& nume, const double& suprafata, const string& tip) {
	Locatar l{ ap,nume,suprafata,tip };
	valid.validate(l);
	repo.add(l);
	undoActions.push_back(make_unique<UndoAdauga>(repo, ap));
	notify();

}

void SrvLocatari::modify(const int& ap, const string& nume, const double& suprafata, const string& tip) {
	if (repo.gasit(ap) == true)
	{
		Locatar lVechi = repo.find_after_apartment(ap);
		int apVechi = lVechi.getApartament();
		string numeVechi = lVechi.getNume();
		double sVeche = lVechi.getSuprafata();
		string tipVechi = lVechi.getTip();
		undoActions.push_back(make_unique<UndoModify>(repo, apVechi, numeVechi, sVeche, tipVechi));
		Locatar l{ ap,nume,suprafata,tip };
		valid.validate(l);
		repo.modify(ap, nume, suprafata, tip);
		notify();
	}
	else
		throw RepoException("\nApartament inexistent!\n");
}

void SrvLocatari::sterge(const int& ap) {
	if (repo.gasit(ap) == true)
	{
		Locatar l = repo.find_after_apartment(ap);
		undoActions.push_back(make_unique<UndoSterge>(repo, l));
		repo.sterge(ap);
		notify();
	}
	else
		throw RepoException("\nApartament inexistent!\n");
}

const Locatar& SrvLocatari::cauta_apartament(const int& ap) {
	return repo.find_after_apartment(ap);

}

//VectDin<Locatar> SrvLocatari::filtrareTipAp(const string& tip)
vector<Locatar> SrvLocatari::filtrareTipAp(const string& tip)
{
	//vector<Locatar> filteredVect(10); asa merge dar am size prea mare
	vector<Locatar> filteredVect;
	vector<Locatar> lista = repo.get_all();
	copy_if(lista.begin(), lista.end(), back_inserter(filteredVect), [&tip](const Locatar& l) { return l.getTip() == tip; });
	return filteredVect;
}

//VectDin<Locatar> SrvLocatari::filtrareSuprafata(const double& suprafata)
vector<Locatar> SrvLocatari::filtrareSuprafata(const double& suprafata)
{
	/*
	VectDin<Locatar> filteredVect;
	for (auto const& l : repo.get_all())
		if (l.getSuprafata() == suprafata)
			filteredVect.push_back(l);
	*/
	vector<Locatar> filteredVect;
	vector<Locatar> lista = repo.get_all();
	copy_if(lista.begin(), lista.end(), back_inserter(filteredVect), [&suprafata](const Locatar& l) noexcept { return l.getSuprafata() == suprafata; });
	return filteredVect;
}

vector<Locatar> SrvLocatari::generalSort(bool(*funct)(const Locatar&, const Locatar&)) {
	/*				pt VectDin
	vector<Locatar> v;
	for (auto const l : repo.get_all())
		v.push_back(l);

	for (int i=0;i<v.size();i++)
		for(int j=i+1;j<v.size();j++)
			if(funct!=nullptr)
			if (!funct(v[i], v[j])) {
				Locatar aux = v[i];
				v[i] = v[j];
				v[j] = aux;
			}
	VectDin<Locatar> v2;
	for (int i = 0; i < v.size(); i++)
		v2.push_back(v[i]);
	return v2;
	*/
	vector<Locatar> v = repo.get_all();
	sort(v.begin(), v.end(), funct);
	return v;

}

//VectDin<Locatar> SrvLocatari::sortByNume()
vector<Locatar> SrvLocatari::sortByNume()
{
	return generalSort(cmpNume);
}

//VectDin<Locatar> SrvLocatari::sortBySuprafata()
vector<Locatar> SrvLocatari::sortBySuprafata()
{
	return generalSort(cmpSuprafata);
}
//VectDin<Locatar> SrvLocatari::sortByTipSuprafata() {
vector<Locatar> SrvLocatari::sortByTipSuprafata() {
	return generalSort(cmpTipSuprafata);
}