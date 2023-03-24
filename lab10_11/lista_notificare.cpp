#include "lista_notificare.h"

using std::shuffle;
using std::default_random_engine;
using std::random_device;

void ListaNotificare::add(const Locatar& loc)
{
	lista_notif.push_back(loc);
}

void ListaNotificare::empty() noexcept
{
	lista_notif.clear();
}

void ListaNotificare::addRandom(vector<Locatar> locatari, int nr)
{
	shuffle(locatari.begin(), locatari.end(), default_random_engine(random_device{}()));
	while (nr && locatari.size() > 0)
	{
		lista_notif.push_back(locatari.back());
		locatari.pop_back();
		nr--;
	}
}

const vector<Locatar>& ListaNotificare::get_all() noexcept
{
	return lista_notif;
}
