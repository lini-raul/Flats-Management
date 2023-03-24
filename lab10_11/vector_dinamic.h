#pragma once
#include "domain.h"

//typedef Locatar Element;

template <typename ElementT>
class IteratorVector;

template <typename ElementT>
class VectDin
{
private:
	int lg;
	int cap;
	ElementT* elems;

	void ensureCapacity();

public:
	//constructor default
	VectDin();

	//constructor copiere
	VectDin(const VectDin& ot);

	//destructor(eliberam memoria)
	~VectDin();

	//operator assignment
	//elibereaza ce era in this
	//aloca spatiu in this
	//copiaza elementele din ot in this
	VectDin& operator=(const VectDin& ot);

	void push_back(const ElementT& el);

	ElementT& get(int poz) const noexcept;
	void set(int poz, const ElementT& el);
	int size() const noexcept;


	friend class IteratorVector<ElementT>;
	IteratorVector<ElementT> begin() noexcept;
	IteratorVector<ElementT> end() noexcept;
	void erase(int poz);
};


template <typename ElementT>
void VectDin<ElementT>::ensureCapacity()
{
	if (lg < cap)
		return; //mai avem loc
	cap *= 2;
	ElementT* aux = elems;
	if (aux != nullptr)
	{
		elems = new ElementT[cap];
		for (int i = 0; i < lg; i++)
			elems[i] = aux[i];
		if (aux != nullptr)
			delete[] aux;
	}

}
template <typename ElementT>
VectDin<ElementT>::VectDin() :elems{ new ElementT[5] }, cap{ 5 }, lg{ 0 }
{
}

template <typename ElementT>
VectDin<ElementT>::VectDin(const VectDin<ElementT>& ot)
{
	elems = new ElementT[ot.cap];
	for (int i = 0; i < ot.lg; i++)
		elems[i] = ot.elems[i];
	lg = ot.lg;
	cap = ot.cap;
}

template <typename ElementT>
VectDin<ElementT>::~VectDin()
{
	if (elems != nullptr)
		delete[] elems;
}

template <typename ElementT>
VectDin<ElementT>& VectDin<ElementT>::operator=(const VectDin<ElementT>& ot)
{
	if (this == &ot)	//daca sunt egale iesi
		return *this;
	if (elems != nullptr)
		delete[] elems;
	elems = new ElementT[ot.cap];
	for (int i = 0; i < ot.lg; i++)
	{
		elems[i] = ot.elems[i];
	}
	lg = ot.lg;
	cap = ot.cap;
	return *this;
}

template <typename ElementT>
void VectDin<ElementT>::push_back(const ElementT& el)
{
	ensureCapacity();
	elems[lg] = el;
	lg++;
}


template <typename ElementT>
ElementT& VectDin<ElementT>::get(int poz) const noexcept
{
	// // O: insert return statement here
	return elems[poz];
}

template <typename ElementT>
void VectDin<ElementT>::set(int poz, const ElementT& el)
{
	elems[poz] = el;
}

template <typename ElementT>
int VectDin<ElementT>::size() const noexcept
{
	return lg;
}

template <typename ElementT>
IteratorVector<ElementT> VectDin<ElementT>::begin() noexcept
{
	return IteratorVector<ElementT>(*this);
}

template <typename ElementT>
IteratorVector<ElementT> VectDin<ElementT>::end() noexcept
{
	return IteratorVector<ElementT>(*this, lg);
}

template <typename ElementT>
void VectDin<ElementT>::erase(int poz)
{
	for (int i = poz; i < lg - 1; i++)
		elems[i] = elems[i + 1];
	lg--;
}





//====================================================================================================
template<typename ElementT>
class IteratorVector
{
private:
	int poz = 0;
	const VectDin<ElementT>& v;
public:
	IteratorVector(const VectDin<ElementT>& v) noexcept;
	IteratorVector(const VectDin<ElementT>& v, int poz) noexcept;
	bool valid()const noexcept;
	ElementT& element()const noexcept;
	int get_poz() const noexcept;
	void next() noexcept;
	ElementT& operator*() noexcept;
	IteratorVector& operator++() noexcept;
	bool operator==(const IteratorVector& ot) noexcept;
	bool operator!=(const IteratorVector& ot) noexcept;
};

template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectDin<ElementT>& v) noexcept : v{ v }
{

}
template<typename ElementT>
IteratorVector<ElementT>::IteratorVector(const VectDin<ElementT>& v, int poz) noexcept : v{ v }, poz{ poz }
{
}
template<typename ElementT>
bool IteratorVector<ElementT>::valid() const noexcept
{
	return poz < v.lg;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::element() const noexcept
{
	// // O: insert return statement here
	return v.elems[poz];
}

template<typename ElementT>
int IteratorVector<ElementT>::get_poz() const noexcept
{
	return poz;
}

template<typename ElementT>
void IteratorVector<ElementT>::next() noexcept
{
	poz += 1;
}

template<typename ElementT>
ElementT& IteratorVector<ElementT>::operator*() noexcept
{
	return element();
}

template<typename ElementT>
IteratorVector<ElementT>& IteratorVector<ElementT>::operator++() noexcept
{
	next();
	return *this;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator==(const IteratorVector<ElementT>& ot) noexcept
{
	return poz == ot.poz;
}

template<typename ElementT>
bool IteratorVector<ElementT>::operator!=(const IteratorVector<ElementT>& ot) noexcept
{
	return !(*this == ot);
}

