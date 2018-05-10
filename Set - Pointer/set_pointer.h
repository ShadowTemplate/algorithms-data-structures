#ifndef _SETP_H
#define _SETP_H

#include "listap.h"
#include "set.h"

template<class T>
class Set_pointer: public Set<T>
{
public:
	typedef typename Set<T>::value_type value_type;

	Set_pointer();
	Set_pointer(Set<T>&);
	Set_pointer(const Set_pointer<T>&);
	~Set_pointer();

	Set_pointer<T>& operator =(Set<T>&);
	bool operator ==(const Set_pointer<T>&) const; // hide this method to let Set_pointer class use Set<T> operator ==
	bool operator !=(const Set_pointer<T>&) const; // hide this method to let Set_pointer class use Set<T> operator !=

	template <class E>
	friend ostream& operator <<(ostream& os, const Set_pointer<E>&); // operator << with CONST set

	void create(); // create the set
	bool empty() const; // true if the set is empty
	bool find(const value_type) const; // true if the element is in the set
	void insert(const value_type); // add an element to the set
	void erase(const value_type); // erase the element from the set
	void unionOp(Set<T>&, Set<T>&); // return the union of the set
	void intersection(Set<T>&, Set<T>&); // return the elements in common
	void difference(Set<T>&, Set<T>&); // return the elements of the 1st set not present in the 2nd set

	value_type pickAny() const; // take one element from the set

private:
	List_pointer<T> set;
};

template<class T>
ostream& operator <<(ostream& os, const Set_pointer<T>& s)
{
	if (s.empty())
		os << "Empty Set" << endl;
	else
	{
		os << "[  ";

		for(typename List_pointer<T>::position p = s.set.begin(); !s.set.end(p); p = s.set.next(p))
			os << s.set.read(p) << "  ";

		os << "]" << endl;
	}

	return os;
}

template<class T>
Set_pointer<T>::Set_pointer()
{
	this->create();
}

template<class T>
Set_pointer<T>::Set_pointer(const Set_pointer<T>& set)
{
	this->create();
	*this = set;
}

template<class T>
Set_pointer<T>::~Set_pointer()
{
	set.clear();
}

template<class T>
Set_pointer<T>& Set_pointer<T>::operator =(Set<T>& s)
{
	if (&s != this) // avoid auto-assignment
	{
		vector<T> elements;
		this->clear();
		while(!s.empty())
		{
			value_type temp = s.pickAny();
			elements.push_back(temp);
			this->insert(temp);
			s.erase(temp);
		}

		while(!elements.empty()) // re-insert the elements in the set
		{
			s.insert(elements.back());
			elements.pop_back();
		}
	}

	return *this;
}

template<class T>
bool Set_pointer<T>::operator ==(const Set_pointer<T>& s) const
{
	if(set.size() != s.set.size())
		return false;

	for(typename List_pointer<T>::position p = set.begin(); !set.end(p); p = set.next(p))
		if(!s.find(set.read(p)))
			return false;

	return true;
}

template<class T>
bool Set_pointer<T>::operator !=(const Set_pointer<T>& set2) const
{
	return (!(*this == set2));
}

template<class T>
void Set_pointer<T>::create()
{
	set.create();
}

template<class T>
bool Set_pointer<T>::empty() const
{
	return set.empty();
}

template<class T>
bool Set_pointer<T>::find(const value_type a) const
{
	return set.find(a);
}

template<class T>
void Set_pointer<T>::insert(const value_type a)
{
	set.add_new(a);
}

template<class T>
void Set_pointer<T>::erase(const value_type a)
{
	if (!set.find(a))
		throw std::logic_error("Set_pointer (exception) - Unable to erase (element not present in the set)");

	set.epurateVal(a);
}

template<class T>
void Set_pointer<T>::unionOp(Set<T>& s1, Set<T>& s2)
{
	this->clear();
	vector<T> elements;

	while (!s1.empty())
	{
		value_type temp = s1.pickAny();
		this->set.add_new(temp);
		elements.push_back(temp);
		s1.erase(temp);
	}

	while(!elements.empty()) // re-insert the elements in the set
	{
		s1.insert(elements.back());
		elements.pop_back();
	}

	while (!s2.empty())
	{
		value_type temp = s2.pickAny();
		this->set.add_new(temp);
		elements.push_back(temp);
		s2.erase(temp);
	}

	while(!elements.empty()) // re-insert the elements in the set
	{
		s2.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
void Set_pointer<T>::intersection(Set<T>& s1, Set<T>& s2)
{
	this->clear();
	vector<T> elements;

	while (!s1.empty())
	{
		value_type temp = s1.pickAny();
		if(s2.find(temp))
			this->set.add_new(temp);
		elements.push_back(temp);
		s1.erase(temp);
	}

	while(!elements.empty()) // re-insert the elements in the set
	{
		s1.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
void Set_pointer<T>::difference(Set<T>& s1, Set<T>& s2)
{
	this->clear();
	vector<T> elements;

	while (!s1.empty())
	{
		value_type temp = s1.pickAny();
		if(!s2.find(temp))
			this->set.add_new(temp);
		elements.push_back(temp);
		s1.erase(temp);
	}

	while(!elements.empty()) // re-insert the elements in the set
	{
		s1.insert(elements.back());
		elements.pop_back();
	}

}

template<class T>
typename Set_pointer<T>::value_type Set_pointer<T>::pickAny() const
{
	if(set.empty())
		throw std::logic_error("Set_pointer (exception) - Unable to pick an element (empty set)");
	
	return set.read(set.begin());
}

#endif // _SETP_H
