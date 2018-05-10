#ifndef _MFSETLIST_H
#define _MFSETLIST_H

#include "mfset.h"
#include "listap.h"
#include "set_pointer.h"

#include <iostream>
#include <stdexcept>
#include <vector>

using std::endl;
using std::ostream;
using std::vector;

template<class T>
class MFSet_list: public MFSet<T, List_pointer<T> >
{
public:
	typedef typename MFSet<T, List_pointer<T> >::value_type value_type;
	typedef typename MFSet<T, List_pointer<T> >::component component;

	MFSet_list();
	MFSet_list(Set<T>&);
	MFSet_list(const MFSet_list<T>&);
	~MFSet_list();

	template<class E>
	friend ostream& operator <<(ostream& os, const MFSet_list<E>& set);

	MFSet_list<T>& operator =(const MFSet_list<T>&);
	bool operator ==(const MFSet_list<T>&) const;
	bool operator !=(const MFSet_list<T>&) const;

	void create(Set<T>&); // create the MFSet
	void merge(const value_type&, const value_type&); // merge to two disjoint components
	component find(const value_type&) const; // return the component in which is present the element

private:
	List_pointer<component> components;
};

template<class T>
ostream& operator <<(ostream& os, const MFSet_list<T>& set)
{
	os << "MFSet: " << endl;

	for (typename List_pointer<List_pointer<T> >::position p = set.components.begin(); !set.components.end(p);
			p = set.components.next(p))
		os << set.components.read(p);

	os << endl;

	return os;
}

template<class T>
MFSet_list<T>::MFSet_list()
{
	components = List_pointer<component>();
}

template<class T>
MFSet_list<T>::MFSet_list(Set<T>& set)
{
	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		elements.push_back(temp);
		set.erase(temp);
		component tempList;
		tempList.push_back(temp);
		components.push_back(tempList);
		tempList.clear();
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
MFSet_list<T>::MFSet_list(const MFSet_list<T>& set2)
{
	components = set2.components;
}

template<class T>
MFSet_list<T>::~MFSet_list()
{
}

template<class T>
MFSet_list<T>& MFSet_list<T>::operator =(const MFSet_list<T>& set)
{
	if (this != &set)
	{
		while (!components.empty())
			components.pop_back();

		for (typename component::position p = set.components.begin(); !set.components.end(p);
				p = set.components.next(p))
			components.push_back(set.components.read(p));
	}

	return *this;
}

template<class T>
bool MFSet_list<T>::operator ==(const MFSet_list<T>& mfset2) const
{
	if (components.size() != mfset2.components.size())
		return false;

	/* convert lists (components) in sets
	 *
	 * two MFSets are equal if they are made of the same components
	 * (the order of the components isn't relevant;
	 * the order of the elements in the components isn't relevant)
	 *
	 * == for set is different from == for list
	 * == for list consider the order of the elements
	 *
	 */

	List_pointer < Set_pointer<T> > l1;
	List_pointer < Set_pointer<T> > l2;

	for(typename List_pointer<component>::position p = components.begin(); !components.end(p); p = components.next(p))
	{
		component currComp = components.read(p);
		Set_pointer<T> temp;
		for(typename component::position currPos = currComp.begin(); !currComp.end(currPos); currPos = currComp.next(currPos))
			temp.insert(currComp.read(currPos));

		l1.push_back(temp);
		temp.clear();
	}

	for(typename List_pointer<component>::position p = mfset2.components.begin(); !mfset2.components.end(p); p = mfset2.components.next(p))
	{
		component currComp = mfset2.components.read(p);
		Set_pointer<T> temp;
		for(typename component::position currPos = currComp.begin(); !currComp.end(currPos); currPos = currComp.next(currPos))
				temp.insert(currComp.read(currPos));

		l2.push_back(temp);
		temp.clear();
	}

	for(typename List_pointer<Set_pointer<T> >::position p = l1.begin(); !l1.end(p); p = l1.next(p))
		if(!l2.find(l1.read(p)))
			return false;

	/* If the order of the elements in a component is relevant,
	 * we can use the operator == for lists (components of the MFSet)
	 * that will be called by the method find

		for(typename List_pointer<component>::position p = components.begin(); !components.end(p); p = components.next(p))
			if(!mfset2.components.find(components.read(p)))
				return false;
	*/

	return true;
}

template<class T>
bool MFSet_list<T>::operator !=(const MFSet_list<T>& mfset2) const
{
	return (!(*this == mfset2));
}

template<class T>
void MFSet_list<T>::create(Set<T>& set)
{
	while (!components.empty())
		components.pop_back();

	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		set.erase(temp);
		component tempList;
		tempList.push_back(temp);
		components.push_back(tempList);
		tempList.clear();
		elements.push_back(temp);
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
void MFSet_list<T>::merge(const value_type& elem1, const value_type& elem2)
{
	if (this->find(elem1) == this->find(elem2))
		throw std::logic_error("MFSet_list (exception) - Unable to merge (non-disjoint components)");

	component temp;
	temp.join(this->find(elem1), this->find(elem2));
	components.push_back(temp);
	components.epurateVal(this->find(elem1));
	components.epurateVal(this->find(elem2));
}

template<class T>
typename MFSet_list<T>::component MFSet_list<T>::find(const value_type& val) const
{
	for (typename List_pointer<component>::position p = components.begin(); !components.end(p);
			p = components.next(p))
		if ((components.read(p)).find(val))
			return components.read(p);

	throw std::logic_error("MFSet_list (exception) - Unable to find component");
}

#endif // _MFSETLIST_H
