#ifndef _MFSETTREE_H
#define _MFSETTREE_H

#include "mfset.h"
#include "N-aryTree_pointer.h"

template<class T>
class MFSet_tree: public MFSet<T, NaryTree_pointer<T> >
{
public:
	typedef typename MFSet<T, NaryTree_pointer<T> >::value_type value_type;
	typedef typename MFSet<T, NaryTree_pointer<T> >::component component;

	MFSet_tree();
	MFSet_tree(Set<T>&);
	MFSet_tree(const MFSet_tree<T>&);
	~MFSet_tree();

	template<class E>
	friend ostream& operator <<(ostream&, const MFSet_tree<E>&);

	MFSet_tree<T>& operator =(const MFSet_tree<T>&);
	bool operator ==(const MFSet_tree<T>&) const;
	bool operator !=(const MFSet_tree<T>&) const;

	void create(Set<T>&); // create the MFSet
	void merge(const value_type&, const value_type&); // merge to two disjoint components
	component find(const value_type&) const; // return the component in which is present the element

private:
	List_pointer<component> components;
};

template<class T>
ostream& operator <<(ostream& os, const MFSet_tree<T>& set)
{
	for (typename List_pointer<NaryTree_pointer<T> >::position p = set.components.begin(); !set.components.end(p);
			p = set.components.next(p))
		os << set.components.read(p);

	return os;
}

template<class T>
MFSet_tree<T>::MFSet_tree()
{
	components = List_pointer<component>();
}

template<class T>
MFSet_tree<T>::MFSet_tree(Set<T>& set)
{
	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		set.erase(temp);
		component tempTree(temp);
		components.push_back(tempTree);
		tempTree.erase(tempTree.root());
		elements.push_back(temp);
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
MFSet_tree<T>::MFSet_tree(const MFSet_tree<T>& set2)
{
	*this = set2;
}

template<class T>
MFSet_tree<T>::~MFSet_tree()
{
}

template<class T>
MFSet_tree<T>& MFSet_tree<T>::operator =(const MFSet_tree<T>& set)
{
	if (this != &set)
	{
		if (!components.empty()) // clear the MFSet
			components.clear();

		components = set.components;
	}

	return *this;
}

template<class T>
bool MFSet_tree<T>::operator ==(const MFSet_tree<T>& mfset2) const
{
	if (components.size() != mfset2.components.size())
		return false;

	/* convert trees (components) in sets
	 *
	 * two MFSets are equal if they are made of the same components
	 * (the order of the components isn't relevant;
	 * the order of the elements in the components isn't relevant)
	 *
	 * == for set is different from == for tree
	 * == for tree consider the order of the elements
	 *
	 */

	List_pointer<Set_pointer<T> > l1;
	List_pointer<Set_pointer<T> > l2;

	for (typename List_pointer<component>::position p = components.begin(); !components.end(p);
			p = components.next(p))
	{
		component currComp = components.read(p);
		vector<T> elements;
		elements = currComp.elementsArray();
		Set_pointer<T> newSet;
		while (!elements.empty())
		{
			newSet.insert(elements.back());
			elements.pop_back();
		}
		l1.push_back(newSet);
		newSet.clear();
	}

	for (typename List_pointer<component>::position p = mfset2.components.begin(); !mfset2.components.end(p);
			p = mfset2.components.next(p))
	{
		component currComp = mfset2.components.read(p);
		vector<T> elements;
		elements = currComp.elementsArray();
		Set_pointer<T> newSet;
		while (!elements.empty())
		{
			newSet.insert(elements.back());
			elements.pop_back();
		}
		l2.push_back(newSet);
		newSet.clear();
	}

	for (typename List_pointer<Set_pointer<T> >::position p = l1.begin(); !l1.end(p); p = l1.next(p))
		if (!l2.find(l1.read(p)))
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
bool MFSet_tree<T>::operator !=(const MFSet_tree<T>& mfset2) const
{
	return (!(*this == mfset2));
}

template<class T>
void MFSet_tree<T>::create(Set<T>& set)
{
	if (!components.empty())
		components.clear();

	vector<value_type> elements;
	while (!set.empty())
	{
		value_type temp = set.pickAny();
		set.erase(temp);
		component tempTree(temp);
		components.push_back(tempTree);
		tempTree.erase(tempTree.root());
		elements.push_back(temp);
	}

	while (!elements.empty()) // re-insert the elements in the set
	{
		set.insert(elements.back());
		elements.pop_back();
	}
}

template<class T>
void MFSet_tree<T>::merge(const value_type& elem1, const value_type& elem2)
{
	component tree1 = this->find(elem1);
	component tree2 = this->find(elem2);

	if (tree1 == tree2)
		throw std::logic_error("MFSet_tree (exception) - Unable to merge (non-disjoint components)");

	components.epurateVal(tree1);
	components.epurateVal(tree2);

	component temp(tree1);

	if(temp.is_leaf(temp.root()))
	{
		temp.insFirstSubTree(temp.root(), tree2);
		components.push_back(temp);
	}
	else
	{
		temp.insSubTree(temp.lastChild(temp.root()), tree2);
		components.push_back(temp);
	}
}

template<class T>
typename MFSet_tree<T>::component MFSet_tree<T>::find(const value_type& val) const
{
	for (typename List_pointer<component>::position p = components.begin(); !components.end(p);
			p = components.next(p))
		if ((components.read(p)).find(val))
			return components.read(p);

	throw std::logic_error("MFSet_tree (exception) - Unable to find component");
}

#endif // _MFSETTREE_H
