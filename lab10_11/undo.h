#pragma once
#include "repository.h"
#include "domain.h"
/*
clasa pur virtuala
*/
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
	int apAdaugat;
	RepoLocatari& repo;
public:
	UndoAdauga(RepoLocatari& repo, const int& ap) :repo{ repo }, apAdaugat{ ap }{}

	void doUndo() override;
};

class UndoSterge : public ActiuneUndo {
	Locatar locSters;
	RepoLocatari& repo;
public:
	UndoSterge(RepoLocatari& repo, const Locatar& loc) :repo{ repo }, locSters{ loc }{}

	void doUndo() override;
};
class UndoModify : public ActiuneUndo {
	RepoLocatari& repo;
	int ap;
	string nume;
	double suprafata;
	string tip;
public:
	UndoModify(RepoLocatari& repo, const int& ap, const string& nume, const double& suprafata, const string& tip) : repo{ repo }, ap{ ap }, nume{ nume }, suprafata{ suprafata }, tip{ tip }{}

	void doUndo() override;
};
