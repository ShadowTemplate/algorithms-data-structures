#ifndef _LISTALIN_H
#define _LISTALIN_H

#include <iostream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

template<class T, class P>
class Linear_list
{
public:

	typedef T value_type;
	typedef P position;

	virtual ~Linear_list() // avoid warnings in compiling
	{
	}

	virtual void create() = 0; // create the list
	virtual bool empty() const = 0; // true if the list is empty
	virtual value_type read(position) const = 0; //read the element in the position
	virtual void write(const value_type&, position) = 0; // write the element at position
	virtual position begin() const = 0; // returns a position pointing to the beginning of the list
	virtual bool end(position) const = 0; // true if the position is the last of the list
	virtual position next(position) const = 0; // returns the next position
	virtual position previous(position) const = 0; // return the previous position
	virtual void insert(const value_type&, position) = 0; // add an element before the position
	virtual void erase(position) = 0; // erases the element in that position

	bool operator ==(const Linear_list<T, P>&) const;
	bool operator !=(const Linear_list<T, P>&) const;

	position endnode() const; // returns a position pointing to the end of the list
	int size() const; // returns the number of element in the list
	void push_front(const value_type&); // insert a new element at the beginning
	void push_back(const value_type&); // insert a new element at the end
	void pop_front(); // removes the first element
	void pop_back(); // removes the last element
	void clear(); // erases all the elements

	bool findOrd(const value_type&) const; // search an element in an ordinated list
	void insOrd(const value_type&); // insert an element in an ordinated list in the right position
	void merge(const Linear_list<T, P>&, const Linear_list<T, P>&); // merge two ordinated list
	void epurate(); //erases duplicates
	bool find(const value_type&) const; // true if the element is in the list
	void add_new(const value_type&); // add the element only if it isn't already in the list
	void join(const Linear_list<T, P>&, const Linear_list<T, P>&); // join two lists
	void sort(); // selection sort on the element of the list
	void reverse(); // change the order of the element
	void common(const Linear_list<T, P>&, const Linear_list<T, P>&); // search the common elements in two lists
	void epurateVal(const value_type&); // epurate all the occurences of the element from the list
};

template<class T, class P>
ostream& operator <<(ostream& os, const Linear_list<T, P>& l)
{
	if (l.empty())
		os << "Empty List" << endl;
	else
	{
		typename Linear_list<T, P>::position p = l.begin();
		os << "[ ";
		while (!l.end(p))
		{
			if (p != l.begin())
				os << ", " << l.read(p);
			else
				os << l.read(p);

			p = l.next(p);
		}
		os << " ]" << endl;
	}

	return os;
}

template<class T, class P>
bool Linear_list<T, P>::operator ==(const Linear_list<T, P>& list2) const
{

	if (list2.size() != this->size())
		return false;

	position p = this->begin();
	position p2 = list2.begin();

	for (int i = 0; i < this->size(); i++)
	{
		if (this->read(p) != list2.read(p2))
			return false;
		else
		{
			p = this->next(p);
			p2 = list2.next(p2);
		}
	}

	return true;
}

template<class T, class P>
bool Linear_list<T, P>::operator !=(const Linear_list<T, P>& list2) const
{
	return (!(*this == list2));
}

template<class T, class P>
typename Linear_list<T, P>::position Linear_list<T, P>::endnode() const
{
	position p = this->begin();

	while (!this->end(this->next(p)))
		p = this->next(p);

	return p;
}

template<class T, class P>
int Linear_list<T, P>::size() const
{
	int len = 0;

	if (!this->empty())
	{
		position p = this->begin();
		len++;

		while (p != this->endnode())
		{
			len++;
			p = this->next(p);
		}
	}
	return len;
}

template<class T, class P>
void Linear_list<T, P>::push_front(const value_type& el)
{
	this->insert(el, this->begin());
}

template<class T, class P>
void Linear_list<T, P>::push_back(const value_type& el)
{
	this->insert(el, this->next(this->endnode()));
}

template<class T, class P>
void Linear_list<T, P>::pop_front()
{
	this->erase(this->begin());
}

template<class T, class P>
void Linear_list<T, P>::pop_back()
{
	this->erase(this->endnode());
}

template<class T, class P>
void Linear_list<T, P>::clear()
{
	position p = this->endnode();
	position temp;
	int len = this->size();

	for (int i = 0; i < len; i++)
	{
		temp = p;
		p = this->previous(p);
		this->erase(temp);
	}
}

template<class T, class P>
bool Linear_list<T, P>::findOrd(const value_type& el) const
{
	bool flag = false;
	int size = this->size();

	position p = this->begin();

	for (int i = 0; (i < size && flag == false && this->read(p) <= el); i++)
	{
		if (this->read(p) == el)
			flag = true;

		p = this->next(p);
	}

	return flag;
}

template<class T, class P>
void Linear_list<T, P>::insOrd(const value_type& el)
{
	position p = this->endnode();

	if (this->empty())
		this->insert(el, this->begin());
	else if (el >= this->read(p))
		this->push_back(el);
	else
	{
		position p = this->begin();
		while (el > this->read(p) && !this->end(p))
			p = this->next(p);

		this->insert(el, p);
	}
}

template<class T, class P>
void Linear_list<T, P>::merge(const Linear_list<T, P>& list1, const Linear_list<T, P>& list2)
{
	for (position p = list1.begin(); !list1.end(p); p = list1.next(p))
		this->push_back(list1.read(p));

	for (position p = list2.begin(); !list2.end(p); p = list2.next(p))
		this->insOrd(list2.read(p));
}

template<class T, class P>
void Linear_list<T, P>::epurate()
{
	if (this->empty())
		throw std::logic_error("Linear List (exception)");

	position p = this->begin();
	position r;
	position q;

	while (!this->end(p))
	{
		q = this->next(p);
		while (!this->end(q))
		{
			if (this->read(p) == this->read(q))
			{
				r = this->previous(q);
				this->erase(q);
				q = r;
			}

			q = this->next(q);
		}
		p = this->next(p);
	}
}

template<class T, class P>
bool Linear_list<T, P>::find(const value_type& el) const
{
	bool flag = false;

	if (!this->empty())
	{
		for (Linear_list<T, P>::position p = this->begin(); !this->end(p); p = this->next(p))
			if (el == this->read(p))
				flag = true;
	}

	return flag;
}

template<class T, class P>
void Linear_list<T, P>::add_new(const value_type& el)
{
	if (!this->find(el))
		this->push_back(el);
}

template<class T, class P>
void Linear_list<T, P>::join(const Linear_list<T, P>& list1, const Linear_list<T, P>& list2)
{
	for (position p = list1.begin(); !list1.end(p); p = list1.next(p))
		this->push_back(list1.read(p));

	for (position p = list2.begin(); !list2.end(p); p = list2.next(p))
		this->push_back(list2.read(p));
}

template<class T, class P>
void Linear_list<T, P>::sort()
{
	if (!this->empty())
	{
		int dim = this->size();
		value_type* elements = new value_type[dim];
		value_type temp;
		int i = 0;

		for (position p = this->begin(); !this->end(p); p = this->next(p))
		{
			elements[i] = this->read(p);
			i++;
		}

		//Selection sort
		int j, imin = 0;
		for (i = 0; i < dim - 1; i++)
		{
			imin = i;
			for (j = i + 1; j < dim; j++)
			{
				if (elements[j] < elements[imin])
					imin = j;
			}

			temp = elements[i];
			elements[i] = elements[imin];
			elements[imin] = temp;
		}

		i = 0;
		for (position p = this->begin(); !this->end(p); p = this->next(p))
		{
			this->write(elements[i], p);
			i++;
		}
	}
}

template<class T, class P>
void Linear_list<T, P>::reverse()
{
	if (!this->empty())
	{
		int dim = this->size();
		dim = dim / 2;
		position p1 = this->begin();
		position p2 = this->endnode();
		value_type temp;

		for (int i = 0; i < dim; i++)
		{
			temp = this->read(p1);
			this->write(this->read(p2), p1);
			this->write(temp, p2);
			p1 = this->next(p1);
			p2 = this->previous(p2);
		}
	}
}

template<class T, class P>
void Linear_list<T, P>::common(const Linear_list<T, P>& list1, const Linear_list<T, P>& list2)
{
	for (position p = list1.begin(); !list1.end(p); p = list1.next(p))
		if ((list2.find(list1.read(p)) && !this->find(list1.read(p))))
			this->push_back(list1.read(p));
}

template<class T, class P>
void Linear_list<T, P>::epurateVal(const value_type& value)
{
	if (!this->empty())
	{
		vector<T> temp;
		for (position p = this->begin(); !this->end(p); p = this->next(p))
			if (this->read(p) != value)
				temp.push_back(this->read(p));

		this->clear();
		for(typename vector<T>::iterator it = temp.begin(); it != temp.end(); it++)
			this->push_back(*it);
	}
}

#endif // _LISTALIN_H
