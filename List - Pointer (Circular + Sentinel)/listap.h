#ifndef _LISTAP_H
#define _LISTAP_H

#include "cellalp.h"
#include "linear_list.h"

template<class T>
class List_pointer: public Linear_list<T, Cell<T>*>
{
public:
	typedef typename Linear_list<T, Cell<T>*>::position position;
	typedef typename Linear_list<T, Cell<T>*>::value_type value_type;

	List_pointer();
	List_pointer(const List_pointer<T>&);
	~List_pointer();

	List_pointer<T>& operator =(const List_pointer<T>&);

	void create(); // create the list
	bool empty() const; // true if the list is empty
	value_type read(position) const; // read the element in the position
	void write(const value_type&, position); // write the element at the position
	position begin() const; // return the position of the first element of the list
	bool end(position) const; // true if the position is the last of the list
	position next(position) const; // return the next position
	position previous(position) const; // return the previous position
	void insert(const value_type&, position); // add an element before the position
	void erase(position); // erase the element in the position

private:
	position list;
};

template<class T>
List_pointer<T>::List_pointer()
{
	this->create();
}

template<class T>
List_pointer<T>::List_pointer(const List_pointer<T>& list)
{
	this->create();
	*this = list;
}

template<class T>
List_pointer<T>::~List_pointer()
{
	this->clear();
}

template<class T>
List_pointer<T>& List_pointer<T>::operator =(const List_pointer<T>& s)
{
	if (&s != this) // avoid auto-assignment
	{
		this->clear();
		position p = s.begin();

		for (int i = 0; i < s.size(); i++)
		{
			this->push_back(s.read(p));
			p = this->next(p);
		}
	}

	return *this;
}

template<class T>
void List_pointer<T>::create()
{
	value_type valueNull = value_type();
	list = new Cell<value_type>(valueNull);
	list->setValue(valueNull);
	list->setNext(list);
	list->setPrev(list);
}

template<class T>
bool List_pointer<T>::empty() const
{
	return ((list->getNext() == list) && (list->getPrev() == list));
}

template<class T>
typename List_pointer<T>::position List_pointer<T>::begin() const
{
	return list->getNext();
}

template<class T>
typename List_pointer<T>::position List_pointer<T>::next(position p) const
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to get next (invalid position)");

	return p->getNext();
}

template<class T>
typename List_pointer<T>::position List_pointer<T>::previous(position p) const
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to get previous (invalid position)");

	return p->getPrev();
}

template<class T>
bool List_pointer<T>::end(position p) const
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to check if is last position (invalid position)");

	return (p == list);
}

template<class T>
typename Linear_list<T, Cell<T>*>::value_type List_pointer<T>::read(position p) const
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to read label (invalid position)");

	return p->getValue();
}

template<class T>
void List_pointer<T>::write(const value_type& a, position p)
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to write label (invalid position)");

	p->setValue(a);
}

template<class T>
void List_pointer<T>::insert(const value_type& a, position p)
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to insert (invalid position)");

	position temp = new Cell<value_type>;

	temp->setValue(a);
	temp->setPrev(p->getPrev());
	temp->setNext(p);
	(p->getPrev())->setNext(temp);
	p->setPrev(temp);
	p = temp;
}

template<class T>
void List_pointer<T>::erase(position p)
{
	if (p == 0)
		throw std::logic_error("List_pointer (exception) - Unable to erase (invalid position)");

	position temp = p;
	(p->getNext())->setPrev(p->getPrev());
	(p->getPrev())->setNext(p->getNext());
	p = p->getNext();
	delete temp;
	temp = 0;
}

#endif // _LISTAP_H
