#pragma once
#include <vector>
using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	vector<Observer*> observers;
protected:
	void notify();
public:
	void addObserver(Observer* obs);
	void removeObserver(Observer* obs);

};