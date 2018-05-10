#ifndef _SETBOOL_H
#define _SETBOOL_H

#include <stdexcept>
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Set_bool
{
public:

	Set_bool();
	Set_bool(int); // size
	Set_bool(const Set_bool&);
	~Set_bool();

	Set_bool& operator =(const Set_bool&);
	bool operator ==(const Set_bool&);
	bool operator !=(const Set_bool&);

	void create(); // create the set
	bool empty() const; // true if the set is empty
	bool find(const int) const; // true if the element is in the set
	void insert(const int); // add an element to the set
	void erase(const int); // erase the element from the set
	void unionOp(const Set_bool&, const Set_bool&); // return the union of the set
	void intersection(const Set_bool&, const Set_bool&); // return the elements in common
	void difference(const Set_bool&, const Set_bool&); // return the elements of the 1st set not present in the 2nd set

	int pickAny() const; // take one element from the set

	void clear();
	int size() const;
	int getLen() const; // return length

private:
	bool* set;
	int length;

	void arrayExpansion(bool*&, const int, const int);
};

ostream& operator <<(ostream& os, const Set_bool& s)
{
	if (s.empty())
		os << "Empty Set" << endl;
	else
	{
		os << "[  ";
		for(int i = 0; i < s.getLen(); i++ )
			if(s.find(i))
				os << i << "  ";

		os << "]" << endl;
	}

	return os;
}

Set_bool::Set_bool()
{
	set = 0;
	length = 10;
	this->create();
}

Set_bool::Set_bool(int dim)
{
	if (dim <= 0)
		throw std::logic_error("Set_bool: exception - Unable to initialize the set (negative or null size)");

	set = 0;
	length = dim;
	this->create();
}

Set_bool::Set_bool(const Set_bool& set)
{
	length = set.length;
	this->create();
	*this = set;
}

Set_bool::~Set_bool()
{
	delete[] set;
}

Set_bool& Set_bool::operator =(const Set_bool& s)
{
	if (&s != this) // avoid auto-assignment
	{
		this->clear();
		length = s.length;
		this->create();
		for (int i = 0; i < s.length; i++)
			set[i] = s.set[i];
	}

	return *this;
}

bool Set_bool::operator ==(const Set_bool& set2)
{
	if(this->size() != set2.size())
		return false;

	for(int i=0; i < length; i++)
		if( set[i] != set2.set[i] )
			return false;

	return true;
}

bool Set_bool::operator !=(const Set_bool& set2)
{
	return (!(*this == set2));
}


void Set_bool::create()
{
	set = new bool[length];
	for( int i = 0; i < length; i++ )
		set[i] = false;
}

bool Set_bool::empty() const
{
	return (this->size() == 0);
}

bool Set_bool::find(const int a) const
{
	if (a >= length)
		return false;

	return set[a];
}

void Set_bool::insert(const int a)
{
	if (a >= length)
		arrayExpansion(set, length, a+1);

	set[a] = true;
}

void Set_bool::erase(const int a)
{
	if (!set[a])
		throw std::logic_error("Set_bool: exception - Unable to erase (element not in the set)");

	set[a] = false;
}

void Set_bool::unionOp(const Set_bool& s1, const Set_bool& s2)
{
	this->clear();

	this->length = s1.length;
	if (s2.length > this->length)
		this->length = s2.length; // this->length = max(s1.length, s2.length)

	this->create();
	for (int i = 0; i < s1.length; i++)
		if (s1.set[i])
			set[i] = true;

	for (int i = 0; i < s2.length; i++)
		if (s2.set[i])
			set[i] = true;
}

void Set_bool::intersection(const Set_bool& s1, const Set_bool& s2)
{
	this->clear();

	this->length = s1.length;
	this->create();

	for (int i = 0; i < s1.length; i++)
		if (s1.set[i] && s2.set[i])
			set[i] = true;
}

void Set_bool::difference(const Set_bool& s1, const Set_bool& s2)
{
	this->clear();

	this->length = s1.length;
	this->create();

	for (int i = 0; i < s1.length; i++)
		if (s1.set[i] && !s2.set[i])
			set[i] = true;
}

int Set_bool::pickAny() const
{
	if(this->size() == 0)
		throw std::logic_error("Set_bool: exception - Unable to pick an element (empty set)");

	for(int i = 0; true; i++)
		if(set[i] == true)
			return i;

	throw std::logic_error("Set_bool: exception - Unable to pick an element (corrupted set)");
}

void Set_bool::clear()
{
	for(int i = 0; i < length; i++ )
		set[i] = false;
}

int Set_bool::size() const
{
	int counter = 0;
	for(int i = 0; i < length; i++ )
		if(set[i] == true)
			counter++;

	return counter;
}

void Set_bool::arrayExpansion(bool*& a, const int oldSize, const int newSize)
{
	bool* temp = new bool[newSize];
	for (int i = 0; i < newSize; i++)
		temp[i] = false;

	for (int i = 0; i < oldSize; i++)
		temp[i] = a[i];

	delete[] a;
	a = temp;

	length = newSize;
}

int Set_bool::getLen() const
{
	return length;
}

#endif // _SETBOOL_H
