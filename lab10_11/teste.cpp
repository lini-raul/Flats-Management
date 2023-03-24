#include "teste.h"
#include "domain.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include "repository.h"
#include "exceptions.h"
#include "validatori.h"
#include "service.h"
#include "vector_dinamic.h"
#include <sstream>
#include <iostream>
#include "lista_notificare.h"
#include <map>
#include <fstream>


using std::cout;
using std::ifstream;
using std::ofstream;
using std::endl;

void Teste::test_creeaza_locatar()
{
	Locatar l{ 1,"Raul",10.1,"decomandat" };
	Locatar l2{ 1,"Raul",10.1,"decomandat" };
	assert(l == l2);
	assert(l.getApartament() == 1);
	assert(l.getNume() == "Raul");
	assert(l.getSuprafata() == 10.1);
	assert(l.getTip() == "decomandat");

	l.setNume("Mihai");
	l.setSuprafata(20.1);
	l.setTip("semidecomandat");

	assert(l.getApartament() == 1);
	assert(l.getNume() == "Mihai");
	assert(l.getSuprafata() == 20.1);
	assert(l.getTip() == "semidecomandat");

}

void Teste::test_repo_locatari_add()
{
	RepoLocatari repo;
	Locatar l{ 1,"Raul",10.1,"decomandat" };
	repo.add(l);
	vector<Locatar>loc = repo.get_all();
	//VectDin loc = repo.get_all();

	assert(loc.size() == 1);

	try {
		repo.add(l);
		//assert(false);
	}
	catch (const RepoException& e)
	{
		assert(true);
		assert(e.getMessage() == "Apartament deja existent!");
	}

	Locatar l2{ 2,"Mihai",20.1,"semidecomandat" };
	repo.add(l2);

	loc = repo.get_all();
	assert(loc.size() == 2);

	Locatar l_gasit = repo.find_after_apartment(2);
	assert(l_gasit.getApartament() == 2);
	assert(l_gasit.getNume() == "Mihai");
	assert(l_gasit.getSuprafata() == 20.1);
	assert(l_gasit.getTip() == "semidecomandat");

	try {
		l_gasit = repo.find_after_apartment(3);
		//assert(false);
	}
	catch (const RepoException& e)
	{
		assert(true);
		assert(e.getMessage() == "Apartament inexistent!");
	}

}

void Teste::test_repo_locatari_modify()
{
	RepoLocatari repo;
	Locatar l{ 1,"Raul",10.1,"decomandat" };
	repo.add(l);
	constexpr int ap = 1;
	string nume = "Mihai";
	constexpr double suprafata = 20.1;
	string tip = "semidecomandat";
	repo.modify(ap, nume, suprafata, tip);
	Locatar l_gasit = repo.find_after_apartment(1);
	assert(l_gasit.getApartament() == 1);
	assert(l_gasit.getNume() == "Mihai");
	assert(l_gasit.getSuprafata() == 20.1);
	assert(l_gasit.getTip() == "semidecomandat");

}

void Teste::test_repo_locatari_sterge() {

	RepoLocatari repo;
	Locatar l{ 1,"Raul",10.1,"decomandat" };
	Locatar l2{ 2,"Mihai",20.1,"semidecomandat" };
	Locatar l3{ 3,"Radu",30.1,"2 camere" };
	Locatar l4{ 4,"Andrei",40.1,"3 camere" };

	repo.add(l);
	repo.add(l2);
	repo.add(l3);
	repo.add(l4);
	auto loc = repo.get_all();
	assert(loc.size() == 4);


	repo.sterge(3);
	loc = repo.get_all();
	assert(loc.size() == 3);   //assertion failed

	Locatar l_gasit = repo.find_after_apartment(2);
	assert(l_gasit.getApartament() == 2);
	assert(l_gasit.getNume() == "Mihai");
	assert(l_gasit.getSuprafata() == 20.1);
	assert(l_gasit.getTip() == "semidecomandat");

	repo.sterge(2);
	repo.sterge(1);
	repo.sterge(4);
	loc = repo.get_all();
	assert(loc.size() == 0);




}

void Teste::test_validator() {
	LocatarValidator v;
	Locatar l{ -1, "",-10.1,"" };
	try {
		v.validate(l);
	}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		//cout << mesaj;
		assert(mesaj == "Apartament negativ! Nume vid! Suprafata negativa! Tip vid! ");

	}

}

void Teste::test_srv_adauga() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	assert(srv.get_all().size() == 1);
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	assert(srv.get_all().size() == 2);
}

void Teste::test_srv_modify() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.modify(1, "Andrei", 30.1, "2 camere");

	Locatar l_gasit = repo.find_after_apartment(1);
	assert(l_gasit.getApartament() == 1);
	assert(l_gasit.getNume() == "Andrei");
	assert(l_gasit.getSuprafata() == 30.1);
	assert(l_gasit.getTip() == "2 camere");

	try {
		srv.modify(5, "Andrei", 30.1, "2 camere");
	}
	catch (const RepoException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		//cout << mesaj;
		assert(mesaj == "\nApartament inexistent!\n");
		//assert(ex.getMessage() == "\nApartament inexistent!\n");
	}



}

void Teste::test_srv_sterge() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	assert(srv.get_all().size() == 3);

	try {
		srv.sterge(5);
	}
	catch (const RepoException& ex)
	{
		assert(ex.getMessage() == "\nApartament inexistent!\n");
	}

	srv.sterge(2);
	assert(srv.get_all().size() == 2);
	srv.sterge(3);
	assert(srv.get_all().size() == 1);
	srv.sterge(1);
	assert(srv.get_all().size() == 0);


}

void Teste::test_srv_cauta_apartament() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");

	Locatar l = srv.cauta_apartament(2);
	assert(l.getApartament() == 2);
	assert(l.getNume() == "Mihai");
	assert(l.getSuprafata() == 20.1);
	assert(l.getTip() == "semidecomandat");

	try {
		srv.cauta_apartament(5);
	}
	catch (const RepoException& ex) {
		assert(ex.getMessage() == "Apartament inexistent!");
	}
}

VectDin<Locatar> Teste::testCopyIterate(VectDin<Locatar> v)
{
	double totalSuprafata = 0;
	for (auto el : v)
	{
		totalSuprafata = totalSuprafata + el.getSuprafata() - 0.1;
	}
	Locatar l{ 10,"Tudor",totalSuprafata,"2 camere" };
	v.push_back(l);
	return v;
}

void Teste::test_vect_din() {

	VectDin<Locatar> v;
	for (int i = 0; i < 10; i++)
	{
		Locatar l{ i,"Raul",i + 0.1,"decomandat" };
		v.push_back(l);
	}
	assert(v.size() == 10);
	assert(v.get(5).getApartament() == 5);

	VectDin<Locatar> v2{ v };
	assert(v2.size() == 10);
	assert(v2.get(5).getApartament() == 5);

	VectDin<Locatar> v3;
	v3 = v;
	assert(v3.size() == 10);
	assert(v3.get(5).getApartament() == 5);


	VectDin v4 = testCopyIterate(v);
	assert(v4.size() == 11);
	assert(v4.get(10).getApartament() == 10);
	assert(v4.get(10).getSuprafata() == 45);

	Locatar l{ 22,"Raul",22.1,"decomandat" };
	v4.set(1, l);
	assert(v4.get(1).getApartament() == 22);
	assert(v4.get(1).getSuprafata() == 22.1);

	IteratorVector it{ v4 };
	assert(it.valid() == true);
	for (int i = 1; i <= 11; i++)
		it.next();
	assert(it.valid() == false);

	v4 = v4;
	assert(v4.get(1).getApartament() == 22);
	assert(v4.get(1).getSuprafata() == 22.1);


}

void Teste::test_srv_filtrare_tip() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	srv.add(4, "Raul", 10.1, "decomandat");
	srv.add(5, "Mihai", 20.1, "semidecomandat");
	srv.add(6, "Andrei", 30.1, "decomandat");

	string tip = "decomandat";
	vector<Locatar> v = srv.filtrareTipAp(tip);
	assert(v.size() == 3);
	// v.at(x) - returneaza prin referinta obiectul de pe pozitia x
	assert(v.at(0).getApartament() == 1);
	assert(v.at(1).getApartament() == 4);
	assert(v.at(2).getApartament() == 6);
	assert(v.at(0).getNume() == "Raul");
	assert(v.at(1).getNume() == "Raul");
	assert(v.at(2).getNume() == "Andrei");
	assert(v.at(0).getTip() == "decomandat");
	assert(v.at(1).getTip() == "decomandat");
	assert(v.at(2).getTip() == "decomandat");
}

void Teste::test_srv_filtrare_suprafata() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	srv.add(4, "Raul", 10.1, "decomandat");
	srv.add(5, "Mihai", 20.1, "semidecomandat");
	srv.add(6, "Andrei", 10.1, "2 camere");

	constexpr double suprafata = 10.1;
	vector<Locatar> v = srv.filtrareSuprafata(suprafata);

	assert(v.size() == 3);
	// v.at(x) - returneaza prin referinta obiectul de pe pozitia x
	assert(v.at(0).getApartament() == 1);
	assert(v.at(1).getApartament() == 4);
	assert(v.at(2).getApartament() == 6);
	assert(v.at(0).getNume() == "Raul");
	assert(v.at(1).getNume() == "Raul");
	assert(v.at(2).getNume() == "Andrei");
	assert(v.at(0).getTip() == "decomandat");
	assert(v.at(1).getTip() == "decomandat");
	assert(v.at(2).getTip() == "2 camere");
}

void Teste::test_srv_sortare() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "2 camere");
	srv.add(3, "Andrei", 30.1, "2 camere");

	vector<Locatar> v = srv.sortByNume();
	assert(v.at(0).getNume() == "Andrei");
	assert(v.at(1).getNume() == "Mihai");
	assert(v.at(2).getNume() == "Raul");

	v = srv.sortByTipSuprafata();
	assert(v.at(0).getApartament() == 2);
	assert(v.at(1).getApartament() == 3);
	assert(v.at(2).getApartament() == 1);

	v = srv.sortBySuprafata();
	assert(v.at(0).getSuprafata() == 10.1);
	assert(v.at(1).getSuprafata() == 20.1);
	assert(v.at(2).getSuprafata() == 30.1);

}

void Teste::test_repo_lista_notif() {
	RepoLocatari repo;
	Locatar l1{ 1,"Raul",10.1,"decomandat" };
	repo.add(l1);
	Locatar l2{ 2,"Raul",20.1,"decomandat" };
	repo.add(l2);
	Locatar l3{ 3,"Raul",30.1,"decomandat" };
	repo.add(l3);
	Locatar l4{ 4,"Raul",40.1,"decomandat" };
	repo.add(l4);
	Locatar l5{ 5,"Raul",50.1,"decomandat" };
	repo.add(l5);

	ListaNotificare lista;

	assert(lista.get_all().size() == 0);
	lista.add(l1);
	assert(lista.get_all().size() == 1);
	lista.addRandom(repo.get_all(), 3);
	assert(lista.get_all().size() == 4);

	lista.empty();
	assert(lista.get_all().size() == 0);
}

void Teste::test_srv_lista_notif() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	srv.add(4, "Raul", 10.1, "decomandat");
	srv.add(5, "Mihai", 20.1, "semidecomandat");
	srv.add(6, "Andrei", 10.1, "2 camere");
	Locatar l{ 3,"Andrei",30.1,"2 camere" };

	assert(srv.get_allListaNotif().size() == 0);
	srv.addToListaNotif(l);
	assert(srv.get_allListaNotif().size() == 1);
	srv.addRandomToListaNotif(4);
	assert(srv.get_allListaNotif().size() == 5);
	srv.addRandomToListaNotif(5);
	assert(srv.get_allListaNotif().size() == 10);
	srv.emptyListaNotif();
	assert(srv.get_allListaNotif().size() == 0);
}

void Teste::test_srv_raport_suprafata() {
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	srv.add(4, "Raul", 10.1, "decomandat");
	srv.add(5, "Mihai", 20.1, "semidecomandat");
	srv.add(6, "Andrei", 10.1, "2 camere");
	srv.add(7, "Andrei", 10.1, "2 camere");

	auto dict = srv.raport_suprafata();
	cout << dict.at(10.1) << "\n";
	cout << dict.at(20.1) << "\n";
	cout << dict.at(30.1) << "\n";
	assert(dict.at(10.1) == 4);
	assert(dict.at(20.1) == 2);
	assert(dict.at(30.1) == 1);

}

void Teste::test_repoFile() {
	ofstream fout;
	fout.open("teste_locatari.txt", ofstream::trunc);
	fout << "1,Raul,10.1,decomandat" << endl;
	fout << "2,Mihai,20.1,semidecomandat" << endl;
	fout << "3,Andrei,30.1,2 camere" << endl;
	fout.close();
	try {
		RepoLocatariFile repo{ "teste_locatari_inv.txt" };
		assert(false);
	}
	catch (RepoException&) {
		assert(true);
	}
	RepoLocatariFile repo{ "teste_locatari.txt" };
	assert(repo.get_all().size() == 3);
	Locatar loc = repo.find_after_apartment(2);
	assert(loc.getNume() == "Mihai");
	assert(loc.getSuprafata() == 20.1);
	assert(loc.getTip() == "semidecomandat");

	Locatar l2{ 4,"Radu",40.1,"3 camere" };
	repo.add(l2);
	assert(repo.get_all().size() == 4);

	repo.sterge(2);
	assert(repo.get_all().size() == 3);
	repo.modify(1, "George", 100.2, "4 camere");
	assert(repo.get_all().size() == 3);
	loc = repo.find_after_apartment(1);
	assert(loc.getNume() == "George");
	assert(loc.getSuprafata() == 100.2);
	assert(loc.getTip() == "4 camere");

}

void Teste::test_undo()
{
	RepoLocatari repo;
	LocatarValidator valid;
	SrvLocatari srv{ repo,valid };

	srv.add(1, "Raul", 10.1, "decomandat");
	srv.add(2, "Mihai", 20.1, "semidecomandat");
	srv.add(3, "Andrei", 30.1, "2 camere");
	srv.add(4, "Raul", 10.1, "decomandat");
	srv.add(5, "Mihai", 20.1, "semidecomandat");
	srv.sterge(4);
	srv.modify(5, "George", 40.1, "3 camere");
	srv.undo();
	Locatar l = srv.cauta_apartament(5);
	assert(l.getApartament() == 5);
	assert(l.getNume() == "Mihai");
	assert(l.getSuprafata() == 20.1);
	assert(l.getTip() == "semidecomandat");

	srv.undo();
	assert(srv.get_all().size() == 5);
	srv.undo();
	assert(srv.get_all().size() == 4);
	srv.undo();
	assert(srv.get_all().size() == 3);



}


void Teste::test_all() {
	cout << "Started tests\n";
	test_creeaza_locatar();
	test_repo_locatari_add();
	test_repo_locatari_modify();
	test_repo_locatari_sterge();		//problems
	test_validator();
	test_srv_adauga();
	test_srv_modify();
	test_srv_sterge();
	test_srv_cauta_apartament();
	test_srv_filtrare_tip();
	test_srv_filtrare_suprafata();
	test_srv_sortare();
	test_repo_lista_notif();
	test_srv_lista_notif();
	test_srv_raport_suprafata();
	test_repoFile();
	test_undo();

	test_vect_din();
	cout << "Finished tests\n\n";
}

