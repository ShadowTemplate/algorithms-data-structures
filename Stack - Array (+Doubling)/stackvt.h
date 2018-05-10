#ifndef _STACKVT_H
#define _STACKVT_H

#include <stdexcept>
#include "stack.h"

template<class T>
class Stack_vector: public Stack<T, int>
{
public:

	typedef typename Stack<T, int>::value_type value_type;

	Stack_vector();
	Stack_vector(int); // size
	Stack_vector(const Stack_vector<T>&);
	~Stack_vector();

	Stack_vector<T>& operator =(const Stack_vector<T>&);

	void create(); // create the stack
	bool empty() const; // true if the stack is empty
	value_type read() const; // return the top of the stack (don't erase it)
	void push(const value_type&); // add an element to the top of the stack
	void pop(); // erase the first element

private:
	value_type* element;
	int maxLen;
	int topIndex;

	void arrayDoubling(value_type*&, const int, const int);
};

template<class T>
Stack_vector<T>::Stack_vector()
{
	maxLen = 25; // default size
	topIndex = 0;
	element = 0;
	this->create();
}

template<class T>
Stack_vector<T>::Stack_vector(int size)
{
	if (size <= 0)
		size = 25; // default size

	maxLen = size;
	topIndex = 0;
	element = 0;
	this->create();
}

template<class T>
Stack_vector<T>::Stack_vector(const Stack_vector<T>& s)
{
	*this = s;
}

template<class T>
Stack_vector<T>::~Stack_vector()
{
	delete[] element;
}

template<class T>
Stack_vector<T>& Stack_vector<T>::operator =(const Stack_vector<T>& s)
{
	if (&s != this) // avoid auto-assignment
	{
		// copy the vector's elements and its size
		this->maxLen = s.maxLen;

		// allocates memory for the vector
		this->create();
		this->topIndex = s.topIndex;

		for (int i = 0; i < this->topIndex; i++)
			this->element[i] = s.element[i];
	}

	return *this;
}

template<class T>
void Stack_vector<T>::create()
{
	element = new value_type[maxLen];
	topIndex = 0;
}

template<class T>
bool Stack_vector<T>::empty() const
{
	return (topIndex == 0);
}

template<class T>
typename Stack_vector<T>::value_type Stack_vector<T>::read() const
{
	if (this->empty())
		throw std::logic_error("Stack_vector: (exception) - Unable to read (empty stack)");

	return element[topIndex - 1];
}

template<class T>
void Stack_vector<T>::push(const value_type& el)
{
	if (topIndex == maxLen)
	{
		this->arrayDoubling(element, maxLen, maxLen * 2);

		topIndex = maxLen;
		maxLen = maxLen * 2;
	}

	element[topIndex] = el;
	topIndex++;
}

template<class T>
void Stack_vector<T>::pop()
{
	if (this->empty())
		throw std::logic_error("Stack_vector: (exception) - Unable to pop (empty stack)");

	topIndex--;
}

template<class T>
void Stack_vector<T>::arrayDoubling(value_type*& a, const int oldSize, const int newSize)
{
	value_type* temp = new value_type[newSize];

	for (int i = 0; i < oldSize; i++)
		temp[i] = a[i];

	delete[] a;
	a = temp;
}

#endif // _STACKVTVT_H
