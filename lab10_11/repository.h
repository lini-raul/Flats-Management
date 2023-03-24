#pragma once
#include "domain.h"
#include <vector>
#include <algorithm>
#include "vector_dinamic.h"


using std::vector;

class RepoLocatari {
private:
	vector<Locatar> locatari;

	//VectDin<Locatar> locatari;

public:
	RepoLocatari() noexcept = default;
	RepoLocatari(const RepoLocatari& ot) = delete;

	virtual void add(const Locatar& loc);
	virtual void modify(const int& ap, const string& nume, const double& suprafata, const string& tip);
	virtual void sterge(const int& ap);

	vector<Locatar> get_all();
	//VectDin<Locatar> get_all();
	const Locatar& find_after_apartment(const int ap);
	bool gasit(const int& ap);

};

class RepoLocatariFile : public RepoLocatari {
private:
	string filename;
	/*
	Incarca datele din fisier
	*/
	void loadFromFile();
	/*
	Salveaza datele in fisier
	Format: apartament,nume,suprafata,tip\n
	*/
	void saveToFile();
public:
	RepoLocatariFile(string fname) : RepoLocatari(), filename{ fname }
	{
		loadFromFile();
	};
	void add(const Locatar& loc) override;
	void modify(const int& ap, const string& nume, const double& suprafata, const string& tip) override;
	void sterge(const int& ap) override;
};
