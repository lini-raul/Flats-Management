#pragma once
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
class Teste {
private:
	void test_creeaza_locatar();
	void test_repo_locatari_add();
	void test_repo_locatari_modify();
	void test_repo_locatari_sterge();
	void test_validator();
	void test_srv_adauga();
	void test_srv_modify();
	void test_srv_sterge();
	void test_srv_cauta_apartament();
	void test_srv_filtrare_tip();
	void test_srv_filtrare_suprafata();
	void test_srv_sortare();
	VectDin<Locatar> testCopyIterate(VectDin<Locatar> v);
	void test_vect_din();
	void test_repo_lista_notif();
	void test_srv_lista_notif();
	void test_srv_raport_suprafata();
	void test_repoFile();
	void test_undo();


public:

	void test_all();

};
