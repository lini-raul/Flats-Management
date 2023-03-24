#pragma once
#include "domain.h"
#include <vector>
#include <random>	// std::default_random_engine

using std::vector;

class ListaNotificare {
private:
	vector<Locatar> lista_notif;
public:
	ListaNotificare() = default;

	/*
	adauga un locatar in lista de notificare
	*/
	void add(const Locatar& loc);

	/*
	goleste lista de notificare
	*/
	void empty() noexcept;


	/*
	adauga un numar dat de locatari random din repo locatari
	*/
	void addRandom(vector<Locatar> locatari, int nr);

	const vector<Locatar>& get_all() noexcept;
};
