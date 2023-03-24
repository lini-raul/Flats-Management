#include "observer.h"

void Observable::notify()
{
	for (auto obs : observers) {
		obs->update();
	}
}

void Observable::addObserver(Observer* obs)
{
	observers.push_back(obs);
}

void Observable::removeObserver(Observer* obs)
{
	remove_if(observers.begin(), observers.end(), [&obs](const Observer* o) noexcept { return obs == o; });
	observers.pop_back();
}
