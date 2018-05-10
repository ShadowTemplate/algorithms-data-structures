#ifndef _QUEUEVT_
#define _QUEUEVT_

#include <stdexcept>
#include "queue.h"

template<class T>
class Queue_vector: public Queue<T, int>
{
public:

	typedef typename Queue<T, int>::value_type value_type;

	Queue_vector();
	Queue_vector(int);
	Queue_vector(const Queue_vector<T>&);
	~Queue_vector();

	Queue_vector<T>& operator =(const Queue_vector<T>&);

	void create(); //create the queue
	bool empty() const; // true if the queue is empty
	value_type read() const; //return the first element of the queue (don't erase it)
	void enqueue(const value_type&); //add an element at the end of the queue
	void dequeue(); //erase the first element of the queue

private:
	void arrayDoubling(value_type*&, const int, const int, const int);

	value_type* element;
	int head, len, maxLen;
};

template<class T>
Queue_vector<T>::Queue_vector()
{
	maxLen = 25;
	head = 0;
	len = 0;
	element = 0;
	this->create();
}

template<class T>
Queue_vector<T>::Queue_vector(int size)
{
	if (size <= 0)
		throw std::logic_error("Queue_vector: exception");

	maxLen = size;
	head = 0;
	len = 0;
	element = 0;
	this->create();
}

template<class T>
Queue_vector<T>::Queue_vector(const Queue_vector<T>& q2)
{
	*this = q2;
}

template<class T>
Queue_vector<T>::~Queue_vector()
{
	delete[] element;
}

template<class T>
Queue_vector<T>& Queue_vector<T>::operator =(const Queue_vector<T>& q2)
{
	// avoid auto-assignment.
	if (&q2 != this)
	{
		// copy the vector's elements and its size
		this->maxLen = q2.maxLen;

		// allocates memory for the element vector
		this->create();
		this->head = q2.head;
		this->len = q2.len;

		for (int i = 0; i < len; i++)
			this->element[((q2.head + i) % this->maxLen)] = q2.element[((q2.head + i) % q2.maxLen)];
	}

	return *this;
}

template<class T>
void Queue_vector<T>::create()
{
	element = new value_type[maxLen];
	head = 0;
	len = 0;
}

template<class T>
bool Queue_vector<T>::empty() const
{
	return (len == 0);
}

template<class T>
typename Queue<T, int>::value_type Queue_vector<T>::read() const
{
	if (this->empty())
		throw std::logic_error("Queue_vector: exception");

	return (element[head]);
}

template<class T>
void Queue_vector<T>::enqueue(const value_type& el)
{
	if (len == maxLen)
	{
		this->arrayDoubling(element, head, maxLen, maxLen * 2);
		head = 0;
		maxLen = maxLen * 2;
	}

	element[(head + len) % maxLen] = el;
	len++;
}

template<class T>
void Queue_vector<T>::dequeue()
{
	if (this->empty())
		throw std::logic_error("Queue_vector: exception");

	head = (head + 1) % maxLen;
	len--;
}

template<class T>
void Queue_vector<T>::arrayDoubling(value_type*& a, const int head, const int oldDim, const int newDim)
{

	value_type* temp = new value_type[newDim];

	for (int i = 0; i < oldDim; i++)
		temp[i] = a[(head + i) % oldDim];

	delete[] a;
	a = temp;
}

#endif //QUEUEVT_
