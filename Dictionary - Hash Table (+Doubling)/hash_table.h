#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <string>
#include <vector>
#include <iostream>

#include "dictionary.h"
#include "hash.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

//Keys are unique. Inserting two times the same keys while cause overwrite of the label

//There is always at least one empty bucket in every moment in the dictionary

template<class K, class E>
class Hash_table: public Dictionary<K, E>
{
public:

	typedef typename Dictionary<K, E>::key key;
	typedef typename Dictionary<K, E>::item element;

	Hash_table();
	Hash_table(int); // size
	Hash_table(const Hash_table<K, E>&);
	~Hash_table();

	Hash_table<K, E>& operator =(const Hash_table<K, E>&); // doesn't copy tombstones
	bool operator ==(const Hash_table<K, E>&) const;
	bool operator !=(const Hash_table<K, E>&) const;

	bool empty() const;
	int size() const;
	Element<K, E>* find(const key&) const;
	void insert(const Element<K, E>);
	void erase(const key& k);
	void modify(const key& k, const element& e);

	int getBucket(const key&) const; // find the home bucket of the tombstone
	int availableBucket(const key&) const; // the same as getBucket, but it doesn't skip tombstone
	vector<K> keyArray() const; // return a vector with the keys of the elements in the dictionary
	vector<E> itemArray() const; // return a vector of the elements in the dictionary
	vector<Element<K, E> > pairArray() const; // return a vector of pairs (element-key) in the dictionary
	bool containsValue(const element&) const; // true if dictionary has the element
	void join(const Hash_table<K, E>&); // add in the implicit dictionary all the elements of the parameter
	bool hasSubset(const Hash_table<K, E>&) const; // true if all the elements in the parameter are present in the implicit dictionary
	bool find(const Element<K, E>) const; // true if the element is present in the dictionary

private:
	Element<K, E>** table; // the hash table
	Hash<K> hashm; // maps type K to non-negative integer
	int dsize; // number of pairs in dictionary
	int MAXSIZE; // hash function divisor
	Element<K, E>* tombstone; // tombstone
	int tombCounter; // number of tombstones

	void create();
	void destroy(); // delete all the element of the dictionary
	void fixTable(); // delete all the tombstones from the dictionary
	void dictionaryDoubling();
};

template<class K, class E>
ostream& operator <<(ostream& out, Hash_table<K, E>& dictionary)
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
Hash_table<K, E>::Hash_table()
{
	MAXSIZE = 97; // default (prime number is better)
	dsize = 0;
	table = 0;
	tombstone = 0;
	tombCounter = 0;
	this->create();
}

template<class K, class E>
Hash_table<K, E>::Hash_table(int size)
{
	MAXSIZE = size;
	dsize = 0;
	table = 0;
	tombstone = 0;
	tombCounter = 0;
	this->create();
}

template<class K, class E>
Hash_table<K, E>::Hash_table(const Hash_table<K, E>& dic2)
{
	*this = dic2;
}

template<class K, class E>
Hash_table<K, E>::~Hash_table()
{
	this->destroy();
	MAXSIZE = 0;
	dsize = 0;
	tombstone = 0;
	tombCounter = 0;
}

template<class K, class E>
Hash_table<K, E>& Hash_table<K, E>::operator =(const Hash_table<K, E>& dic2)
{
	if (this != &dic2)
	{
		this->destroy();
		this->MAXSIZE = dic2.MAXSIZE;
		this->create();

		for (int i = 0; i < dic2.MAXSIZE; i++)
			if (dic2.table[i] != 0 && dic2.table[i] != dic2.tombstone) // epurates the tombstones
				this->insert(*(dic2.table[i]));
	}
	return *this;
}

template<class K, class E>
bool Hash_table<K, E>::operator ==(const Hash_table<K, E>& t) const
{
	if (this->dsize != t.dsize)
		return false;

	if (this->hasSubset(t) && t.hasSubset(*this))
		return true;

	return false;
}

template<class K, class E>
bool Hash_table<K, E>::operator !=(const Hash_table<K, E>& t) const
{
	return (!(*this == t));
}

template<class K, class E>
void Hash_table<K, E>::create()
{
	table = new Element<K, E>*[MAXSIZE];
	for (int i = 0; i < MAXSIZE; i++)
		table[i] = 0;

	tombstone = new Element<K, E>;
	tombCounter = 0;
}

template<class K, class E>
bool Hash_table<K, E>::empty() const
{
	return (dsize == 0);
}

template<class K, class E>
int Hash_table<K, E>::size() const
{
	return dsize;
}

template<class K, class E>
Element<K, E>* Hash_table<K, E>::find(const key& the_key) const
{
	int b = getBucket(the_key);

	if (table[b] == 0)
		return 0;

	return table[b];
}

template<class K, class E>
void Hash_table<K, E>::insert(const Element<K, E> the_pair)
{
	if (((10 * (dsize + 1)) / 7) >= MAXSIZE) // if the dictionary will be full at 70% (at least) with the element you are going to add
		this->dictionaryDoubling();

	int b = availableBucket(the_pair.getKey());

	if (table[b] == 0)
	{
		table[b] = new Element<K, E>(the_pair);
		dsize++;
	}
	else if (table[b] == tombstone)
	{
		table[b] = new Element<K, E>(the_pair);
		dsize++;
		tombCounter--;
	}
	else
	{
		if (table[b]->getKey() == the_pair.getKey())
			table[b]->setItem(the_pair.getItem());
	}
}

template<class K, class E>
void Hash_table<K, E>::erase(const key & k)
{
	int bucket = this->getBucket(k);

	if (table[bucket] == 0)
		throw std::logic_error("Hash_table (exception) - Unable to erase (key not present)");

	delete table[bucket];
	table[bucket] = tombstone;
	dsize--;
	tombCounter++;

	if ((tombCounter * 5) >= MAXSIZE) // if the dictionary is full at 20% (at least) of tombstones
		this->fixTable();
}

template<class K, class E>
void Hash_table<K, E>::destroy()
{
	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] == tombstone)
			table[i] = 0;

	delete tombstone;
	tombstone = 0;

	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] != 0)
		{
			delete table[i];
			table[i] = 0;
		}

	delete[] table;
	table = 0;

	dsize = 0;
}

template<class K, class E>
void Hash_table<K, E>::modify(const key& k, const element& e)
{
	Element<K, E>* b = this->find(k);

	if (b == 0)
		throw std::logic_error("Hash_table (exception) - Unable to modify element (key not present)");
	else
		b->setItem(e);
}

template<class K, class E>
int Hash_table<K, E>::getBucket(const key& the_key) const
{
	int i = (int) hashm(the_key) % MAXSIZE; // i = home bucket
	if (i < 0 || i >= MAXSIZE)
		i = 0;

	int j = i;
	do
	{
		if (table[j] != tombstone && (table[j] == 0 || table[j]->getKey() == the_key)) // skip tombstones
			return j;
		j = (j + 1) % MAXSIZE; // the next bucket
	} while (j != i);

	throw std::logic_error("Hash_table (exception) - Unable to get bucket");
}

template<class K, class E>
int Hash_table<K, E>::availableBucket(const key& the_key) const
{
	int i = (int) hashm(the_key) % MAXSIZE; // i = home bucket
	if (i < 0 || i >= MAXSIZE)
		i = 0;

	int j = i;
	do
	{
		if (table[j] == tombstone || table[j] == 0 || table[j]->getKey() == the_key)
			return j;
		j = (j + 1) % MAXSIZE; // the next bucket
	} while (j != i);

	throw std::logic_error("Hash_table (exception) - Unable to get bucket");
}

template<class K, class E>
vector<K> Hash_table<K, E>::keyArray() const
{
	vector<K> keys;

	if (!this->empty())
		for (int i = 0; i < MAXSIZE; i++)
			if (table[i] != 0 && table[i] != tombstone)
				keys.push_back(table[i]->getKey());

	return keys;
}

template<class K, class E>
vector<E> Hash_table<K, E>::itemArray() const
{
	vector<E> items;

	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] != 0 && table[i] != tombstone)
			items.push_back(table[i]->getItem());

	return items;

}

template<class K, class E>
vector<Element<K, E> > Hash_table<K, E>::pairArray() const
{
	vector<Element<K, E> > pairs;

	if (!this->empty())
		for (int i = 0; i < this->MAXSIZE; i++)
			if (this->table[i] != 0 && table[i] != tombstone)
				pairs.push_back(*this->table[i]);

	return pairs;
}

template<class K, class E>
bool Hash_table<K, E>::containsValue(const element& el) const
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
void Hash_table<K, E>::join(const Hash_table<K, E>& ht2)
{
	if (!ht2.empty())
		for (int i = 0; i < ht2.MAXSIZE; i++)
			if (ht2.table[i] != 0 && ht2.table[i] != tombstone)
				this->insert(*ht2.table[i]);
}

template<class K, class E>
bool Hash_table<K, E>::hasSubset(const Hash_table<K, E>& ht2) const
{
	if ((this->empty() && ht2.empty()) || ht2.empty())
		return true;

	if (this->empty())
		return false;

	vector<Element<K, E> > pairs = ht2.pairArray();
	for (typename vector<Element<K, E> >::iterator it = pairs.begin(); it != pairs.end(); it++)
		if (!this->find(*it))
			return false;

	return true;
}

template<class K, class E>
bool Hash_table<K, E>::find(const Element<K, E> el) const
{
	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] != 0 && table[i] != tombstone && *table[i] == el)
			return true;

	return false;
}

template<class K, class E>
void Hash_table<K, E>::dictionaryDoubling()
{
	vector<Element<K, E> > elements;

	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] != 0 && table[i] != tombstone)
			elements.push_back(*table[i]);

	this->destroy();
	MAXSIZE = MAXSIZE * 2;
	this->create();
	for (typename vector<Element<K, E> >::iterator it = elements.begin(); it != elements.end(); it++)
		this->insert(*it);
}

template<class K, class E>
void Hash_table<K, E>::fixTable()
{
	vector<Element<K, E> > elements;

	for (int i = 0; i < MAXSIZE; i++)
		if (table[i] != 0 && table[i] != tombstone)
			elements.push_back(*table[i]);

	this->destroy();
	this->create();
	for (typename vector<Element<K, E> >::iterator it = elements.begin(); it != elements.end(); it++)
		this->insert(*it);
}

#endif //HASH_TABLE_H
