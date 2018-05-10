#ifndef _QUEUEPT_
#define _QUEUEPT_

#include <stdexcept>
#include "queue.h"
#include "elemqp.h"

template<class T>
class Queue_pointer: public Queue<T, Element<T>*>
{
public:

	typedef typename Queue<T, Element<T>*>::value_type value_type;
	typedef typename Queue<T, Element<T>*>::position elemp;

	Queue_pointer();
	Queue_pointer(const Queue_pointer<T>&);
	~Queue_pointer();

	Queue_pointer<T>& operator =(const Queue_pointer<T>&);

	void create(); // create the queue
	bool empty() const; // true if the queue is empty
	value_type read() const; // return the first element of the queue (don't erase it)
	void enqueue(const value_type&); // add an element at the end of the queue
	void dequeue(); // erase the first element of the queue

private:

	elemp head;
	elemp tail;
};

template<class T>
Queue_pointer<T>::Queue_pointer()
{
	head = 0;
	tail = 0;
}

template<class T>
Queue_pointer<T>::Queue_pointer(const Queue_pointer<T>& q2)
{
	*this = q2;
}

template<class T>
Queue_pointer<T>::~Queue_pointer()
{
	this->clear();
	head = 0;
	tail = 0;
}

template<class T>
Queue_pointer<T>& Queue_pointer<T>::operator =(const Queue_pointer<T>& q2)
{
	if (&q2 != this) // avoid auto-assignment
	{
		elemp currElem = q2.head;

		while (currElem != 0)
		{
			this->enqueue(currElem->getValue());
			currElem = currElem->getNext();
		}
	}

	return *this;
}

template<class T>
void Queue_pointer<T>::create()
{
	this->clear();
	head = 0;
	tail = 0;
}

template<class T>
bool Queue_pointer<T>::empty() const
{
	return (head == 0);
}

template<class T>
typename Queue<T, Element<T>*>::value_type Queue_pointer<T>::read() const
{
	if (this->empty())
		throw std::logic_error("Queue_pointer (exception) - Unable to read (empty queue)");

	return head->getValue();
}

template<class T>
void Queue_pointer<T>::enqueue(const value_type& el)
{
	elemp newtail = new Element<value_type>;
	newtail->setValue(el);

	if (tail == 0)
		head = newtail;
	else
	{
		newtail->setPrev(tail);
		tail->setNext(newtail);
	}
	tail = newtail;
}

template<class T>
void Queue_pointer<T>::dequeue()
{
	if (this->empty())
		throw std::logic_error("Queue_pointer (exception) - Unable to dequeue (empty queue)");

	elemp newhead = head->getNext();
	delete head;
	head = 0;
	if (newhead != 0)
	{
		head = newhead;
		head->setPrev(0);
	}
	else
		tail = 0;
}

#endif //_QUEUEPT_
