#ifndef _SET_H
#define _SET_H

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

template<class T>
class Set
{
public:

	typedef T value_type;

	virtual ~Set()
	{
	}

	virtual void create() = 0; // create the set
	virtual bool empty() const = 0; // true if the set is empty
	virtual bool find(const value_type) const = 0; // true if the element is in the set
	virtual void insert(const value_type) = 0; // add an element to the set
	virtual void erase(const value_type) = 0; // erase the element from the set
	virtual void unionOp(Set<T>&, Set<T>&) = 0; // return the union of the set
	virtual void intersection(Set<T>&, Set<T>&) = 0; // return the elements in common
	virtual void difference(Set<T>&, Set<T>&) = 0; // return the elements of the 1st set not present in the 2nd set

	virtual value_type pickAny() const = 0; // take one element from the set

	bool operator ==(Set<T>&);
	bool operator !=(Set<T>&);

	int size();
	void clear();

};

template<class T>
ostream& operator <<(ostream& os, Set<T>& s)
{
	if (s.empty())
		os << "Empty Set" << endl;
	else
	{
		vector<T> elements;
		os << "[  ";
		while (!s.empty())
		{
			T temp = s.pickAny();
			os << temp << "  ";
			elements.push_back(temp);
			s.erase(temp);
		}
		os << "]" << endl;

		for (typename vector<T>::iterator it = elements.begin(); it != elements.end(); it++)
			s.insert(*it);
	}

	return os;
}

template<class T>
bool Set<T>::operator ==(Set<T>& set2)
{
	if(this->size() != set2.size())
		return false;

	vector<T> elem1;
	vector<T> elem2;
	bool flag = true;

	while (!this->empty())
	{
		value_type temp = this->pickAny();
		elem1.push_back(temp);
		this->erase(temp);
	}

	while (!set2.empty())
	{
		value_type temp = set2.pickAny();
		elem2.push_back(temp);
		set2.erase(temp);
	}

	for(typename vector<T>::iterator it = elem1.begin(); it != elem1.end(); it++)
		if (std::find(elem2.begin(), elem2.end(), *it) == elem2.end()) // if the element isn't present
			flag = false;

	for(typename vector<T>::iterator it = elem1.begin(); it != elem1.end(); it++)
		this->insert(*it);

	for(typename vector<T>::iterator it = elem2.begin(); it != elem2.end(); it++)
		set2.insert(*it);

	return flag;
}

template<class T>
bool Set<T>::operator !=(Set<T>& set2)
{
	return (!(*this == set2));
}

template<class T>
int Set<T>::size()
{
	int len = 0;
	vector<value_type> elements;

	while (!this->empty())
	{
		value_type temp = this->pickAny();
		elements.push_back(temp);
		this->erase(temp);
		len++;
	}

	for (typename vector<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
		this->insert(*it);

	return len;
}

template<class T>
void Set<T>::clear()
{
	while (!this->empty())
	{
		value_type temp = this->pickAny();
		this->erase(temp);
	}
}

#endif // _SET_H
