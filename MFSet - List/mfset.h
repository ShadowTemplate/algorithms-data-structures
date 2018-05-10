#ifndef _MFSET_H
#define _MFSET_H

#include "set.h"

template<class T, class C>
class MFSet
{
public:

	typedef T value_type;
	typedef C component;

	virtual ~MFSet()
	{
	}

	virtual void create(Set<T>&) = 0; // create the MFSet
	virtual void merge (const value_type&, const value_type&) = 0; // merge to two disjoint components
	virtual component find(const value_type&) const = 0; // return the component in which is present the element

	bool findSame(const value_type&, const value_type&) const; // true if the elements are in the same component

};

template<class T, class C>
bool MFSet<T, C>::findSame(const value_type& elem1, const value_type& elem2) const
{
	if(this->find(elem1) == this->find(elem2))
		return true;

	return false;
}

#endif // _MFSET_H
