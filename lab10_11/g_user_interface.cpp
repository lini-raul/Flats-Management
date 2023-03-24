#include "g_user_interface.h"
using std::pair;

void GUserInterface::initGUICmps()
{
	srv.addObserver(this);
	setLayout(lyMain);

	//partea din stanga cu lista si butoanele de sortare
	QWidget* widStanga = new QWidget;
	QVBoxLayout* vl = new QVBoxLayout;
	widStanga->setLayout(vl);
	lst = new QListWidget;
	vl->addWidget(lst);

	QWidget* widBtnStangaSort = new QWidget;
	QHBoxLayout* lyBtnStSort = new QHBoxLayout;
	widBtnStangaSort->setLayout(lyBtnStSort);
	btnSortByNume = new QPushButton("Name Sort");
	lyBtnStSort->addWidget(btnSortByNume);
	btnSortBySuprafata = new QPushButton("Supr Sort");
	lyBtnStSort->addWidget(btnSortBySuprafata);
	btnSortByTipSuprafata = new QPushButton("TipSupr Sort");
	lyBtnStSort->addWidget(btnSortByTipSuprafata);


	QWidget* widBtnStangaFilter = new QWidget;
	QHBoxLayout* lyBtnStFilter = new QHBoxLayout;
	widBtnStangaFilter->setLayout(lyBtnStFilter);
	btnFilterByTip = new QPushButton("Filtrare dupa tip");
	lyBtnStFilter->addWidget(btnFilterByTip);
	btnFilterBySuprafata = new QPushButton("Filtrare dupa suprafata");
	lyBtnStFilter->addWidget(btnFilterBySuprafata);

	vl->addWidget(widBtnStangaSort);
	vl->addWidget(widBtnStangaFilter);
	lyMain->addWidget(widStanga);

	//form pentru detalii
	QWidget* widDetalii = new QWidget;
	QFormLayout* formDetalii = new QFormLayout;
	widDetalii->setLayout(formDetalii);
	txtApartament = new QLineEdit;
	txtNume = new QLineEdit;
	txtSuprafata = new QLineEdit;
	txtTip = new QLineEdit;

	formDetalii->addRow(new QLabel("Apartament: "), txtApartament);
	formDetalii->addRow(new QLabel("Nume: "), txtNume);
	formDetalii->addRow(new QLabel("Suprafata: "), txtSuprafata);
	formDetalii->addRow(new QLabel("Tip: "), txtTip);

	btnAdd = new QPushButton("Add");
	btnModify = new QPushButton("Modify");
	btnDelete = new QPushButton("Delete");
	btnUndo = new QPushButton("Undo");
	formDetalii->addWidget(btnAdd);
	formDetalii->addWidget(btnModify);
	formDetalii->addWidget(btnDelete);
	formDetalii->addWidget(btnUndo);
	formDetalii->addWidget(btnAddLista);
	formDetalii->addWidget(btnAddRandomLista);
	formDetalii->addWidget(btnEmptyLista);

	lyMain->addWidget(widDetalii);

	btnDyn->setLayout(lyBtnDyn);
	lyMain->addWidget(btnDyn);



	//fereastra filtrare dupa suprafata
	filterSuprafata->setLayout(lyfs);
	widTextSupr->setLayout(formlys);
	formlys->addRow(new QLabel("Dati o suprafata: "), textSuprafata);
	btnSupr->setText("Filtreaza");
	lyfs->addWidget(widTextSupr);
	lyfs->addWidget(btnSupr);
	///////////////////////////////////////////


	//fereastra filtrare dupa tip
	filterTip->setLayout(lyft);
	widTextTip->setLayout(formlyt);
	formlyt->addRow(new QLabel("Dati un tip: "), textTip);
	btnTip->setText("Filtreaza");
	lyft->addWidget(widTextTip);
	lyft->addWidget(btnTip);
	/////////////////////////////////////////

	//fereastra lista notif

	int noLines = 10;
	int noColumns = 4;
	listaNotif = new QTableWidget{ noLines, noColumns };

	notif->setLayout(lyNotif);
	lyNotif->addWidget(listaNotif);

	QStringList tblHeaderList;
	tblHeaderList << "Apartament" << "Nume" << "Suprafata" << "Tip";
	listaNotif->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	listaNotif->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

}

void GUserInterface::connectSignalsSlots()
{
	QObject::connect(btnSortByNume, &QPushButton::clicked,this, [&]() {
		qDebug() << "am sortat dupa nume";
		reloadList(srv.sortByNume());
		});

	QObject::connect(btnSortBySuprafata, &QPushButton::clicked, [&]() {
		qDebug() << "am sortat dupa suprafata";
		reloadList(srv.sortBySuprafata());
		});
	QObject::connect(btnSortByTipSuprafata, &QPushButton::clicked, [&]() {
		qDebug() << "am sortat dupa tip si suprafata";
		reloadList(srv.sortByTipSuprafata());
		});

	QObject::connect(btnFilterBySuprafata, &QPushButton::clicked, this, &GUserInterface::filterBySuprafata);
	QObject::connect(btnFilterByTip, &QPushButton::clicked, this, &GUserInterface::filterByTip);

	QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]() {
		auto sel = lst->selectedItems();	//returneaza o lista
		if (sel.isEmpty())
		{
			txtApartament->setText("");
			txtNume->setText("");
			txtSuprafata->setText("");
			txtTip->setText("");
		}
		else {
			auto selItem = sel[0];
			auto nume = selItem->text();
			int ap = selItem->data(Qt::UserRole).toInt();
			Locatar l = srv.cauta_apartament(ap);
			txtApartament->setText(QString::number(l.getApartament()));
			txtNume->setText(nume);
			txtSuprafata->setText(QString::number(l.getSuprafata()));
			txtTip->setText(QString::fromStdString(l.getTip()));
		}
		});

	QObject::connect(btnAdd, &QPushButton::clicked, this, &GUserInterface::addLoc);
	//QObject::connect(btnAdd, &QPushButton::clicked, this, &GUserInterface::adauga_butoane);
	QObject::connect(btnModify, &QPushButton::clicked, this, &GUserInterface::modifyLoc);
	QObject::connect(btnDelete, &QPushButton::clicked, this, &GUserInterface::deleteLoc);
	QObject::connect(btnUndo, &QPushButton::clicked, this, &GUserInterface::undo);

	QObject::connect(btnAddLista, &QPushButton::clicked, this, &GUserInterface::addLista);
	QObject::connect(btnAddRandomLista, &QPushButton::clicked, this, &GUserInterface::addRandomLista);
	QObject::connect(btnEmptyLista, &QPushButton::clicked, this, &GUserInterface::emptyLista);



}

void GUserInterface::reloadList(const vector<Locatar>& locatari)
{
	lst->clear();
	for (const auto& loc : locatari)
	{
		QListWidgetItem* l = new QListWidgetItem( QString::fromStdString(loc.getNume()));
		l->setData(Qt::UserRole, loc.getApartament());
		//if (loc.getNume() == "Raul")
			//l->setData(Qt::BackgroundRole, QBrush{ Qt::yellow, Qt::SolidPattern });
		lst->addItem(l);
	}
}

void GUserInterface::addLoc()
{
	try {
		srv.add(txtApartament->text().toInt(), txtNume->text().toStdString(), txtSuprafata->text().toDouble(), txtTip->text().toStdString());
		reloadList(srv.get_all());
		auto it = dictDyn.find(txtTip->text().toStdString());
		if (it != dictDyn.end())
		{
			int nr = dict[it->first];
			dict[it->first] = nr + 1;
			QPushButton* b = it->second;
			disconnect(b, nullptr, nullptr, nullptr);
			QPushButton::connect(b, &QPushButton::clicked, [this, b, nr]() {
				QMessageBox::information(nullptr, "Info", QString::number(nr+1));
				dictDyn.erase(b->text().toStdString());
				delete b;
				}
			);
		}
		else
		{
			auto btn = new QPushButton{ txtTip->text() };
			dictDyn.insert(pair<string, QPushButton*>(txtTip->text().toStdString(), btn));
			lyBtnDyn->addWidget(btn);
			int nr = 0;
			for (auto const& l : srv.get_all())
			{
				if (l.getTip() == txtTip->text().toStdString())
					nr++;
			}
			dict[txtTip->text().toStdString()] = nr;

			QObject::connect(btn, &QPushButton::clicked, [this, btn,nr]() {
				
				QMessageBox::information(nullptr, "Info", QString::number(nr));
				dictDyn.erase(btn->text().toStdString());
				delete btn;
				});
			
		}

	}
	catch (RepoException &ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void GUserInterface::modifyLoc()
{
	try {
		Locatar l = srv.cauta_apartament(txtApartament->text().toInt());
		string tipVechi = l.getTip();
		srv.modify(txtApartament->text().toInt(), txtNume->text().toStdString(), txtSuprafata->text().toDouble(), txtTip->text().toStdString());
		string tipNou = txtTip->text().toStdString();
		if (dict[tipVechi] == 1)
		{
			auto btn = dictDyn[tipVechi];
			delete btn;
			dict.erase(tipVechi);
			dictDyn.erase(tipVechi);
		}
		else
		{
			dict[tipVechi]--;
			QPushButton* b = dictDyn[tipVechi];
			disconnect(b, nullptr, nullptr, nullptr);
			int nr = dict[tipVechi];
			QPushButton::connect(b, &QPushButton::clicked, [this, b, nr]() {
				QMessageBox::information(nullptr, "Info", QString::number(nr));
				dictDyn.erase(b->text().toStdString());
				delete b;
				}
			);
		}
		auto it = dictDyn.find(tipNou);
		if (it != dictDyn.end())
		{
			int nr = dict[it->first];
			dict[it->first] = nr + 1;
			QPushButton* b = it->second;
			disconnect(b, nullptr, nullptr, nullptr);
			QPushButton::connect(b, &QPushButton::clicked, [this, b, nr]() {
				QMessageBox::information(nullptr, "Info", QString::number(nr + 1));
				dictDyn.erase(b->text().toStdString());
				delete b;
				}
			);
		}
		else
		{
			auto btn = new QPushButton{ txtTip->text() };
			dictDyn.insert(pair<string, QPushButton*>(txtTip->text().toStdString(), btn));
			lyBtnDyn->addWidget(btn);
			int nr = 0;
			for (auto const& l : srv.get_all())
			{
				if (l.getTip() == txtTip->text().toStdString())
					nr++;
			}
			dict[txtTip->text().toStdString()] = nr;

			QObject::connect(btn, &QPushButton::clicked, [this, btn, nr]() {

				QMessageBox::information(nullptr, "Info", QString::number(nr));
				dictDyn.erase(btn->text().toStdString());
				delete btn;
				});
		}
		reloadList(srv.get_all());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void GUserInterface::deleteLoc()
{
	try {
		Locatar l = srv.cauta_apartament(txtApartament->text().toInt());
		srv.sterge(txtApartament->text().toInt());
		if (dict[l.getTip()] == 1)
		{
			auto btn = dictDyn[l.getTip()];
			delete btn;
			dict.erase(l.getTip());
			dictDyn.erase(l.getTip());
		}
		else
		{
			dict[l.getTip()]--;
			QPushButton* b = dictDyn[l.getTip()];
			disconnect(b, nullptr, nullptr, nullptr);
			int nr = dict[l.getTip()];
			QPushButton::connect(b, &QPushButton::clicked, [this, b, nr]() {
				QMessageBox::information(nullptr, "Info", QString::number(nr));
				dictDyn.erase(b->text().toStdString());
				delete b;
				}
			);

		}
		reloadList(srv.get_all());
		
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void GUserInterface::undo()
{
	try {
		srv.undo();
		reloadList(srv.get_all());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void GUserInterface::filterBySuprafata()
{
	filterSuprafata->show();
		
		QObject::connect(btnSupr, &QPushButton::clicked, this, [&]() {
			lst->clear();
			for (const auto& l : srv.get_all()) {
				QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(l.getNume()));
				item->setData(Qt::UserRole, l.getApartament());
				if (l.getSuprafata() == textSuprafata->text().toDouble()) {
					item->setData(Qt::BackgroundRole, QBrush{ Qt::red, Qt::SolidPattern });
				}
				lst->addItem(item);

			}
			filterSuprafata->hide();
			});
}
	
void GUserInterface::filterByTip()
{
	filterTip->show();

	QObject::connect(btnTip, &QPushButton::clicked, this, [&]() {
		lst->clear();
		for (const auto& l : srv.get_all()) {
			QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(l.getNume()));
			item->setData(Qt::UserRole, l.getApartament());
			if (l.getTip() == textTip->text().toStdString()) {
				item->setData(Qt::BackgroundRole, QBrush{ Qt::green, Qt::SolidPattern });
			}
			lst->addItem(item);

		}
		filterTip->hide();
		});
}

void GUserInterface::addLista()
{
	try {
		Locatar loc(txtApartament->text().toInt(), txtNume->text().toStdString(), txtSuprafata->text().toDouble(), txtTip->text().toStdString());
		srv.addToListaNotif(loc);
		reloadListaNotif(srv.get_allListaNotif());
		

	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}

}

void GUserInterface::addRandomLista()
{
	try {
		Locatar loc(txtApartament->text().toInt(), txtNume->text().toStdString(), txtSuprafata->text().toDouble(), txtTip->text().toStdString());
		srv.addRandomToListaNotif(3);
		reloadListaNotif(srv.get_allListaNotif());
	}
	catch (RepoException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
	catch (ValidateException& ex) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
	}
}

void GUserInterface::emptyLista()
{
	srv.emptyListaNotif();
	reloadListaNotif(srv.get_allListaNotif());
}

void GUserInterface::reloadListaNotif(const vector<Locatar>& locatari)
{
	listaNotif->clearContents();
	listaNotif->setRowCount(locatari.size());

	int lineNumber = 0;
	for (auto& loc : locatari)
	{
		listaNotif->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(loc.getApartament())));
		listaNotif->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(loc.getNume())));
		listaNotif->setItem(lineNumber, 2, new QTableWidgetItem(QString::number(loc.getSuprafata())));
		listaNotif->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(loc.getTip())));
		lineNumber++;
	}
}

void GUserInterface::adauga_butoane()
{
	const vector<Locatar>& locatari = srv.get_all();
	
	for (auto const& l : locatari)
	{

		auto it = dict.find(l.getTip());
		if (it == dict.end())
		{
			dict.insert(pair<string, int>(l.getTip(), 1));
		}
		else
		{
			dict.at(l.getTip())++;
		}
	}
	for (const auto& [tip, value] : dict) {

		auto btn = new QPushButton{ QString::fromStdString(tip) };
		dictDyn.insert(pair<string, QPushButton*>(tip, btn));
		lyBtnDyn->addWidget(btn);
		auto nr = value;
		QObject::connect(btn, &QPushButton::clicked, [this, btn, nr]() {
			QMessageBox::information(nullptr, "Info", QString::number(nr));
			dictDyn.erase(btn->text().toStdString());
			delete btn;

			}
		);
	}
	
}

void GUserInterface::update()
{
	reloadList(srv.get_all());
}
