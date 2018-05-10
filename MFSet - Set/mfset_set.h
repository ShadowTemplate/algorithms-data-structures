#ifndef _MFSETSET_H
#define _MFSETSET_H

#include "mfset.h"

#include <iostream>
#include <stdexcept>
#include <vector>

using std::endl;
using std::ostream;
using std::vector;

template<class T>
class MFSet_set: public MFSet<T, Set_pointer<T> >
{
public:
	typedef typename MFSet<T, Set_pointer<T> >::value_type value_type;
	typedef typename MFSet<T, Set_pointer<T> >::component component;

	MFSet_set();
	MFSet_set(Set<T>&);
	MFSet_set(MFSet_set<T>&);
	~MFSet_set();

	template<class E>
	friend ostream& operator <<(ostream&, MFSet_set<E>&);

	MFSet_set<T>& operator =(MFSet_set<T>&);
	bool operator ==(MFSet_set<T>&);
	bool operator !=(MFSet_set<T>&);

	void create(Set<T>&); // create the MFSet
	void merge(const value_type&, const value_type&); // merge to two disjoint components
	component find(const value_type&); // return the component in which is present the element

	component find(const value_type&) const // will always be ignored
	{ // (it's const - impossible to retrieve a set without disassembling it)
		throw std::logic_error("MFSet_set (exception) - Unable to retrieve component");
	}

private:
	Set_pointer<component> components;
};

template<class T>
ostream& operator <<(ostream& os, MFSet_set<T>& set)
{
	os << "MFSet: " << endl;

	MFSet_set<T> temp = set;
	while (!temp.components.empty())
	{
		Set_pointer<T> curr = temp.components.pickAny();
		temp.components.erase(curr);
		os << curr;
	}

	os << endl;

	return os;
}

template<class T>
MFSet_set<T>::MFSet_set()
{
	components = Set_pointer<component>();
}

template<class T>
MFSet_set<T>::MFSet_set(Set<T>& set)
{
	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		elements.push_back(temp);
		set.erase(temp);
		component tempSet;
		tempSet.insert(temp);
		components.insert(tempSet);
		tempSet.clear();
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
MFSet_set<T>::MFSet_set(MFSet_set<T>& set2)
{
	*this = set2;
}

template<class T>
MFSet_set<T>::~MFSet_set()
{
}

template<class T>
MFSet_set<T>& MFSet_set<T>::operator =(MFSet_set<T>& set)
{
	if (this != &set)
	{
		while (!components.empty()) // clear the MFSet
		{
			component temp = components.pickAny();
			components.erase(temp);
		}

		components = set.components;
	}

	return *this;
}

template<class T>
bool MFSet_set<T>::operator ==(MFSet_set<T>& mfset2)
{
	if (components.size() != mfset2.components.size())
		return false;

	bool flag = true;
	vector<component> backup;

	while(!components.empty())
	{
		component temp = components.pickAny();
		backup.push_back(temp);
		components.erase(temp);

		if(!mfset2.components.find(temp))
			flag = false;
	}

	while(!backup.empty())
	{
		components.insert(backup.back());
		backup.pop_back();
	}

	return flag;
}

template<class T>
bool MFSet_set<T>::operator !=(MFSet_set<T>& mfset2)
{
	return (!(*this == mfset2));
}

template<class T>
void MFSet_set<T>::create(Set<T>& set)
{
	if (!components.empty())
		components.clear();

	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		elements.push_back(temp);
		set.erase(temp);
		component tempSet;
		tempSet.insert(temp);
		components.insert(tempSet);
		tempSet.clear();
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
void MFSet_set<T>::merge(const value_type& elem1, const value_type& elem2)
{
	component comp1 = this->find(elem1);
	component comp2 = this->find(elem2);

	if (comp1 == comp2)
		throw std::logic_error("MFSet_set (exception) - Unable to merge (non-disjoint sets)");

	component temp;
	temp.unionOp(comp1, comp2);
	components.insert(temp);
	components.erase(comp1);
	components.erase(comp2);
}

template<class T>
typename MFSet_set<T>::component MFSet_set<T>::find(const value_type& val)
{
	Set_pointer<component> backup;
	backup = components;
	while (!backup.empty())
	{
		component temp = backup.pickAny();
		backup.erase(temp);
		if (temp.find(val))
			return temp;
	}

	throw std::logic_error("MFSet_set (exception) - Unable to find component");
}

#endif // _MFSETSET_H
