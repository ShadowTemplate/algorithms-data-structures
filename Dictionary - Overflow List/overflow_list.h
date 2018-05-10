#ifndef _OVERFLOW_LIST_H
#define _OVERFLOW_LIST_H

#include <vector>
#include <iostream>
#include <algorithm>

#include "dictionary.h"
#include "hash.h"
#include "listap.h"

using std::vector;
using std::cout;
using std::endl;

//Keys are unique. Inserting two times the same keys while cause overwrite of the label

//There is always at least one empty bucket in every moment in the dictionary

template<class K, class E>
class Overflow_list: public Dictionary<K, E>
{
public:

	typedef typename Dictionary<K, E>::key key;
	typedef typename Dictionary<K, E>::item element;

	Overflow_list();
	Overflow_list(int); // size
	Overflow_list(const Overflow_list<K, E>&);
	~Overflow_list();

	Overflow_list<K, E>& operator =(const Overflow_list<K, E>&);
	bool operator ==(const Overflow_list<K, E>&) const;
	bool operator !=(const Overflow_list<K, E>&) const;

	bool empty() const;
	int size() const;
	Element<K, E>* find(const key&) const;
	void insert(const Element<K, E>);
	void erase(const key& k);
	void modify(const key& k, const element& e);

	int getBucket(const key&) const; // find the home bucket of the tombstone
	vector<K> keyArray() const;
	vector<E> itemArray() const;
	vector<Element<K, E> > pairArray() const;
	bool containsValue(const element&) const;
	void join(const Overflow_list<K, E>&); // add in the implicit dictionary all the elements of the parameter
	bool hasSubset(const Overflow_list<K, E>&) const; // true if all the elements in the parameter are present in the implicit dictionary
	bool find(const Element<K, E>) const; // true if the element is present in the dictionary

private:

	List_pointer<Element<K, E>*>* lists; // overflow lists
	Hash<K> hashm; // maps type K to non-negative integer
	int MAXSIZE; // hash function divisor
	int dsize; // number of elements in the dictionary

	void create();
	void destroy(); // delete all the element of the dictionary
};

template<class K, class E>
ostream& operator <<(ostream& out, Overflow_list<K, E>& dictionary)
{
	if (!dictionary.empty())
	{
		vector<K> keys = dictionary.keyArray();
		for (typename vector<K>::iterator it = keys.begin(); it != keys.end(); it++)
		{
			out << *(dictionary.find(*it));
			out << endl;
		}
	}
	else
		out << "Empty Dictionary" << endl;

	out << endl;
	return out;
}

template<class K, class E>
Overflow_list<K, E>::Overflow_list()
{
	lists = 0;
	MAXSIZE = 97; // default size (prime number is better)
	dsize = 0;
	this->create();
}

template<class K, class E>
Overflow_list<K, E>::Overflow_list(int size)
{
	lists = 0;
	MAXSIZE = size;
	dsize = 0;
	this->create();
}

template<class K, class E>
Overflow_list<K, E>::Overflow_list(const Overflow_list<K, E>& dic2)
{
	*this = dic2;
}

template<class K, class E>
Overflow_list<K, E>::~Overflow_list()
{
	this->destroy();
}

template<class K, class E>
Overflow_list<K, E>& Overflow_list<K, E>::operator =(const Overflow_list<K, E>& dic2)
{
	if (this != &dic2)
	{
		this->destroy();
		this->MAXSIZE = dic2.MAXSIZE;
		this->create();

		vector<Element<K, E> > pairs = dic2.pairArray();
		while (!pairs.empty())
		{
			this->insert(pairs.back());
			pairs.pop_back();
		}
	}

	return *this;
}

template<class K, class E>
bool Overflow_list<K, E>::operator ==(const Overflow_list<K, E>& d) const
{
	if (this->dsize != d.dsize)
		return false;

	if (this->hasSubset(d) && d.hasSubset(*this))
		return true;

	return false;
}

template<class K, class E>
bool Overflow_list<K, E>::operator !=(const Overflow_list<K, E>& d) const
{
	return (!(*this == d));
}

template<class K, class E>
void Overflow_list<K, E>::create()
{
	lists = new List_pointer<Element<K, E>*> [MAXSIZE];
}

template<class K, class E>
bool Overflow_list<K, E>::empty() const
{
	return (dsize == 0);
}

template<class K, class E>
int Overflow_list<K, E>::size() const
{
	return dsize;
}

template<class K, class E>
Element<K, E>* Overflow_list<K, E>::find(const key& the_key) const
{
	int b = getBucket(the_key);

	for (typename List_pointer<Element<K, E>*>::position p = lists[b].begin(); !lists[b].end(p);
			p = lists[b].next(p))
		if ((lists[b].read(p))->getKey() == the_key)
			return lists[b].read(p);

	return 0;
}

template<class K, class E>
void Overflow_list<K, E>::insert(const Element<K, E> the_pair)
{
	int b = getBucket(the_pair.getKey());

	if (!this->find(the_pair))
	{
		Element<K, E>* temp = new Element<K, E>(the_pair);
		lists[b].push_back(temp);
		dsize++;
	}
	else
		this->modify(the_pair.getKey(), the_pair.getItem());
}

template<class K, class E>
void Overflow_list<K, E>::erase(const key & k)
{
	if (this->find(k) == 0)
		throw std::logic_error("Overflow_list (exception) - Unable to erase (key not present)");

	int b = this->getBucket(k);
	lists[b].epurateVal(this->find(k));
	dsize--;
}

template<class K, class E>
void Overflow_list<K, E>::destroy()
{
	for (int i = 0; i < MAXSIZE; i++)
		while(!lists[i].empty())
		{
			delete lists[i].read(lists[i].begin());
			lists[i].pop_front();
		}

	delete[] lists;
	lists = 0;

	dsize = 0;
}

template<class K, class E>
void Overflow_list<K, E>::modify(const key& k, const element& e)
{
	Element<K, E>* b = this->find(k);

	if (b == 0)
		throw std::logic_error("Overflow_list (exception) - Unable to modify (key not present)");

	b->setItem(e);
}

template<class K, class E>
int Overflow_list<K, E>::getBucket(const key& the_key) const
{
	int i = (int) hashm(the_key) % MAXSIZE; // i = home bucket

	if (i < 0 || i >= MAXSIZE)
		i = 0;

	return i;
}

template<class K, class E>
vector<K> Overflow_list<K, E>::keyArray() const
{
	vector<K> keys;

	if (!this->empty())
		for (int i = 0; i < MAXSIZE; i++)
			if (!lists[i].empty())
				for (typename List_pointer<Element<K, E>*>::position p = lists[i].begin(); !lists[i].end(p);
						p = lists[i].next(p))
					keys.push_back((lists[i].read(p))->getKey());

	return keys;
}

template<class K, class E>
vector<E> Overflow_list<K, E>::itemArray() const
{
	vector<E> items;

	if (!this->empty())
		for (int i = 0; i < MAXSIZE; i++)
			if (!lists[i].empty())
				for (typename List_pointer<Element<K, E>*>::position p = lists[i].begin(); !lists[i].end(p);
						p = lists[i].next(p))
					items.push_back((lists[i].read(p))->getItem());

	return items;
}

template<class K, class E>
vector<Element<K, E> > Overflow_list<K, E>::pairArray() const
{
	vector<Element<K, E> > pairs;

	if (!this->empty())
		for (int i = 0; i < MAXSIZE; i++)
			if (!lists[i].empty())
				for (typename List_pointer<Element<K, E>*>::position p = lists[i].begin(); !lists[i].end(p);
						p = lists[i].next(p))
					pairs.push_back(*(lists[i].read(p)));

	return pairs;
}

template<class K, class E>
bool Overflow_list<K, E>::containsValue(const element& el) const
{
	if (this->empty())
		return false;

	vector<element> elements = this->itemArray();
	for (typename vector<element>::iterator it = elements.begin(); it != elements.end(); it++)
		if (*it == el)
			return true;

	return false;
}

template<class K, class E>
void Overflow_list<K, E>::join(const Overflow_list<K, E>& d2)
{
	if (!d2.empty())
	{
		vector<Element<K, E> > pairs = d2.pairArray();
		for (typename vector<Element<K, E> >::iterator it = pairs.begin(); it != pairs.end(); it++)
			this->insert(*it);
	}
}

template<class K, class E>
bool Overflow_list<K, E>::hasSubset(const Overflow_list<K, E>& d2) const
{
	if ((this->empty() && d2.empty()) || d2.empty())
		return true;

	if (this->empty())
		return false;

	vector<Element<K, E> > pairs = d2.pairArray();
	for (typename vector<Element<K, E> >::iterator it = pairs.begin(); it != pairs.end(); it++)
		if (!this->find(*it))
			return false;

	return true;
}

template<class K, class E>
bool Overflow_list<K, E>::find(const Element<K, E> el) const
{
	vector<Element<K, E> > pairs = this->pairArray();

	if (std::find(pairs.begin(), pairs.end(), el) != pairs.end())
		return true;

	return false;
}

#endif //_OVERFLOW_LIST_H
