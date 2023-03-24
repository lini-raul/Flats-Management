#pragma once
#include <qwidget.h>
#include "service.h"
#include "repository.h"
#include "domain.h"
#include "exceptions.h"
#include "validatori.h"
#include <map>
#include "histograma.h"

#include "qboxlayout.h"
#include "qlistwidget.h"
#include "qpushbutton.h"
#include "qlineedit.h"
#include "qformlayout.h"
#include "qlabel.h"
#include "qtablewidget.h"
#include "qmessagebox.h"
#include <QHeaderView>



//LABORATOR 11 WISHLISTUL  SA FIE CU TABELE

class GUserInterface : public QWidget, public Observer {
private:
	SrvLocatari& srv;
	QHBoxLayout* lyMain = new QHBoxLayout;
	QListWidget* lst;
	QPushButton* btnSortByNume;
	QPushButton* btnSortBySuprafata;
	QPushButton* btnSortByTipSuprafata;
	QPushButton* btnFilterByTip;
	QPushButton* btnFilterBySuprafata;

	QLineEdit* txtApartament;
	QLineEdit* txtNume;
	QLineEdit* txtSuprafata;
	QLineEdit* txtTip;

	QPushButton* btnAdd;
	QPushButton* btnModify;
	QPushButton* btnDelete;
	QPushButton* btnUndo;

	QVBoxLayout* lyBtnDyn = new QVBoxLayout;
	QWidget* btnDyn = new QWidget;

	map<string, int> dict;
	map<string, QPushButton*> dictDyn;

	//fereastra filtrare dupa suprafata
	QWidget* filterSuprafata = new QWidget;
	QVBoxLayout* lyfs = new QVBoxLayout;
	QWidget* widTextSupr = new QWidget;
	QFormLayout* formlys = new QFormLayout;
	QLineEdit* textSuprafata = new QLineEdit;
	QPushButton* btnSupr = new QPushButton;
	///////////////////////////////////////


	//fereastra filtrare dupa tip
	QWidget* filterTip = new QWidget;
	QVBoxLayout* lyft = new QVBoxLayout;
	QWidget* widTextTip = new QWidget;
	QFormLayout* formlyt = new QFormLayout;
	QLineEdit* textTip = new QLineEdit;
	QPushButton* btnTip = new QPushButton;
	/////////////////////////////////////////

	//fereastra lista notificare
	QWidget* notif = new QWidget;
	QVBoxLayout* lyNotif = new QVBoxLayout;
	QTableWidget* listaNotif = new QTableWidget;
	QPushButton* btnAddLista = new QPushButton("Add in list");
	QPushButton* btnEmptyLista = new QPushButton("Empty list");
	QPushButton* btnAddRandomLista = new QPushButton("Add random in list");
	////////////////////////////////////


	Histograma HistoGUI{srv};




	void initGUICmps();
	void connectSignalsSlots();
	void reloadList(const vector<Locatar>& locatari);
	void addLoc();
	void modifyLoc();
	void deleteLoc();
	void undo();
	void filterBySuprafata();
	void filterByTip();

	void addLista();
	void addRandomLista();
	void emptyLista();


	void reloadListaNotif(const vector<Locatar>& locatari);
	void adauga_butoane();

	void update() override;
public:
	GUserInterface(SrvLocatari& srv) : srv{ srv } {
		initGUICmps();
		connectSignalsSlots();
		reloadList(srv.get_all());
		reloadListaNotif(srv.get_allListaNotif());
		adauga_butoane();
		notif->show();
		HistoGUI.show();
	}
};