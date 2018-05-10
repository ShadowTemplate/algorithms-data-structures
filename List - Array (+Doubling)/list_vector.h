#ifndef _LISTVT_H
#define _LISTVT_H

#include "linear_list.h"

template<class T>
class List_vector: public Linear_list<T, int>
{
public:
	typedef typename Linear_list<T, int>::value_type value_type;
	typedef typename Linear_list<T, int>::position position;

	List_vector();
	List_vector(int); // size
	List_vector(const List_vector<T>&);
	~List_vector();

	List_vector<T>& operator =(const List_vector<T>&);

	void create(); //create the list
	bool empty() const; // true if the list is empty
	value_type read(position) const; //read the element in the position
	void write(const value_type&, position); // write the element at position
	position begin() const; // returns a position pointing to the beginning of the list
	bool end(position) const; // true if the position is the last of the list
	position next(position) const; // returns the next position
	position previous(position) const; // return the previous position
	void insert(const value_type&, position); // add an element before the position
	void erase(position pos); // erases the element in that position

private:
	void arrayDoubling(value_type*&, const int, const int);
	value_type* elements_;
	int length_; // the length of the list
	int array_dimension_; // array's dimension
};

template<class T>
List_vector<T>::List_vector()
{
	elements_ = 0;
	length_ = 0;
	array_dimension_ = 10;
	this->create();
}

template<class T>
List_vector<T>::List_vector(int dim)
{
	if (dim <= 0)
		dim = 10; // default size

	elements_ = 0;
	length_ = 0;
	array_dimension_ = dim;
	this->create();
}

template<class T>
List_vector<T>::List_vector(const List_vector<T>& Lista)
{
	this->array_dimension_ = Lista.array_dimension_;
	this->length_ = Lista.length_;
	this->elements_ = new value_type[array_dimension_];
	for (int i = 0; i < Lista.array_dimension_; i++)
		this->elements_[i] = Lista.elements_[i];
}

template<class T>
List_vector<T>::~List_vector()
{
	delete[] elements_;
}

template<class T>
List_vector<T>& List_vector<T>::operator =(const List_vector<T>& l)
{
	if (this != &l)
	{
		this->array_dimension_ = l.array_dimension_;
		this->length_ = l.length_;
		delete this->elements_;
		this->elements_ = new value_type[array_dimension_];
		for (int i = 0; i < l.array_dimension_; i++)
			this->elements_[i] = l.elements_[i];
	}
	return *this;
}

template<class T>
void List_vector<T>::create()
{
	this->elements_ = new value_type[array_dimension_];
	this->length_ = 0;
}

template<class T>
bool List_vector<T>::empty() const
{
	return (length_ == 0);
}

template<class T>
typename List_vector<T>::position List_vector<T>::begin() const
{
	return 1;
}

template<class T>
typename List_vector<T>::position List_vector<T>::next(position p) const
{
	if ((0 < p) && (p < length_ + 1))
		return (p + 1);
	else
		return p;
}

template<class T>
typename List_vector<T>::position List_vector<T>::previous(position p) const
{
	if ((1 < p) && (p < length_ + 1))
		return (p - 1);
	else
		return p;
}

template<class T>
bool List_vector<T>::end(position p) const
{
	if ((0 < p) && (p <= length_ + 1))
		return (p == length_ + 1);
	else
		return false;
}

template<class T>
typename List_vector<T>::value_type List_vector<T>::read(position p) const
{
	if ((0 < p) && (p < length_ + 1))
		return (elements_[p - 1]);
	else
		throw std::logic_error("List_vector: (exception) - Unable to read node (invalid position)");
}

template<class T>
void List_vector<T>::write(const value_type& a, position p)
{
	if ((0 < p) && (p < length_ + 1))
		elements_[p - 1] = a;
	else
		throw std::logic_error("List_vector: (exception) - Unable to write value (invalid position)");
}

template<class T>
void List_vector<T>::insert(const value_type &a, position p)
{
	if ((0 < p) && (p <= length_ + 1))
	{
		if (length_ == array_dimension_)
		{
			arrayDoubling(elements_, array_dimension_, array_dimension_ * 2);
			array_dimension_ = array_dimension_ * 2;
		}

		for (int i = length_; i >= p; i--)
			elements_[i] = elements_[i - 1];
		elements_[p - 1] = a;
		length_++;
	}
	else
		throw std::logic_error("List_vector: (exception) - Unable to insert node (invalid position)");
}

template<class T>
void List_vector<T>::erase(position p)
{
	if (this->empty())
		throw std::logic_error("List_vector: (exception) - Unable to erase node (empty list)");

	if ((0 < p) && (p < length_ + 1))
	{
		for (int i = p - 1; i < (length_ - 1); i++)
			elements_[i] = elements_[i + 1];
		length_--;
	}
	else
		throw std::logic_error("List_vector: (exception) - Unable to erase node (invalid position)");
}

template<class T>
void List_vector<T>::arrayDoubling(value_type*& a, const int vecchiaDim, const int nuovaDim)
{
	value_type* temp = new value_type[nuovaDim];
	int number;
	if (vecchiaDim < nuovaDim)
		number = vecchiaDim;
	else
		number = nuovaDim;

	for (int i = 0; i < number; i++)
		temp[i] = a[i];

	delete[] a;
	a = temp;
}

#endif // _LISTVT_H
