#pragma once
#include "repository.h"
#include "lista_notificare.h"
#include "validatori.h"
#include <map>
#include <vector>
#include "undo.h"
#include "observer.h"

using std::unique_ptr;

using std::map;

class SrvLocatari: public Observable{
private:
	RepoLocatari& repo;
	LocatarValidator& valid;
	ListaNotificare lista_notif_curenta;
	vector<unique_ptr<ActiuneUndo>> undoActions;

public:

	SrvLocatari(RepoLocatari& repo, LocatarValidator& valid) noexcept :repo{ repo }, valid{ valid } {
	}

	SrvLocatari(const SrvLocatari& ot) = delete;
	void add(const int& ap, const string& nume, const double& suprafata, const string& tip);
	void modify(const int& ap, const string& nume, const double& suprafata, const string& tip);
	void sterge(const int& ap);
	const Locatar& cauta_apartament(const int& ap);
	//VectDin<Locatar> filtrareTipAp(const string& tip);
	//VectDin<Locatar> filtrareSuprafata(const double& suprafata);
	vector<Locatar> filtrareTipAp(const string& tip);
	vector<Locatar> filtrareSuprafata(const double& suprafata);
	//VectDin<Locatar> generalSort(bool(*funct)(const Locatar&, const Locatar&));
	//VectDin<Locatar> sortByNume();
	//VectDin<Locatar> sortBySuprafata();
	//VectDin<Locatar> sortByTipSuprafata();
	vector<Locatar> generalSort(bool(*funct)(const Locatar&, const Locatar&));
	vector<Locatar> sortByNume();
	vector<Locatar> sortBySuprafata();
	vector<Locatar> sortByTipSuprafata();
	const vector<Locatar> get_all();

	void addToListaNotif(const Locatar& loc);
	void addRandomToListaNotif(int nr);
	void emptyListaNotif() noexcept;
	const vector<Locatar>& get_allListaNotif() noexcept;
	void undo();

	const map<double, int> raport_suprafata();


	//VectDin<Locatar> get_all(); pt VectDin

};
