#ifndef _PQLIST_H_
#define _PQLIST_H_

#include "priority_queue.h"
#include "elempq.h"
#include "listap.h"

// Labels can be duplicated
// Priority can be duplicated
// For numbers: minimum number = max priority; for string: first in alphabetical order = max priority
// Can't change one item's label
// Can't change one item's priority

template<class T, class P>
class PriorityQueue_list: public PriorQueue<Elem<T, P>, P>
{

public:
	typedef typename PriorQueue<Elem<T, P>, P>::elem elem;
	typedef typename PriorQueue<Elem<T, P>, P>::priority priority;
	typedef T value_type;

	PriorityQueue_list();
	PriorityQueue_list(const PriorityQueue_list<T, P>&);
	~PriorityQueue_list();

	PriorityQueue_list<T, P>& operator =(const PriorityQueue_list<T, P>&);
	bool operator == (const PriorityQueue_list<T, P>&);
	bool operator != (const PriorityQueue_list<T, P>&);

	bool empty() const; // true if the queue is empty
	void insert(const elem&); // insert an element in the queue
	void pop(); // delete the first element having highest priority
	elem getMin() const; // return the the first element with the highest priority
	elem getMax() const; // return the the last element with the lowest priority

	void insert(const value_type&, const priority&); // insert an element in the queue
	void erasePriorities(const priority&); // erase all the elements having that priority
	void eraseItems(const value_type&); // erase all the elements having that items

private:
	List_pointer<Elem<T, P> > queue;

	void create(); // create the queue
};

template<class T, class P>
PriorityQueue_list<T, P>::PriorityQueue_list()
{
	this->create();
}

template<class T, class P>
PriorityQueue_list<T, P>::PriorityQueue_list(const PriorityQueue_list<T, P>& queue)
{
	this->create();
	*this = queue;
}

template<class T, class P>
PriorityQueue_list<T, P>::~PriorityQueue_list()
{
	this->clear();
}

template<class T, class P>
PriorityQueue_list<T, P>& PriorityQueue_list<T, P>::operator =(const PriorityQueue_list<T, P>& queue2)
{
	if (&queue2 != this) // avoid auto-assignment
	{
		if (!this->queue.empty())
			this->queue.clear();

		this->queue = queue2.queue;
	}

	return *this;
}

template<class T, class P>
bool PriorityQueue_list<T, P>::operator == (const PriorityQueue_list<T, P>& h2)
{
	return (this->queue == h2.queue);
}

template<class T, class P>
bool PriorityQueue_list<T, P>::operator != (const PriorityQueue_list<T, P>& h2)
{
	return (!(*this == h2));
}

template<class T, class P>
bool PriorityQueue_list<T, P>::empty() const
{
	return queue.empty();
}

template<class T, class P>
void PriorityQueue_list<T, P>::insert(const elem& e)
{
	queue.insOrd(e);
}

template<class T, class P>
void PriorityQueue_list<T, P>::insert(const value_type& val, const priority& pri)
{
	this->insert(Elem<T, P>(val, pri));
}

template<class T, class P>
void PriorityQueue_list<T, P>::pop()
{
	if (this->empty())
		throw std::logic_error("PriorityQueue_list (exception) - Unable to pop (empty queue)");

	queue.pop_front();
}

template<class T, class P>
typename PriorityQueue_list<T, P>::elem PriorityQueue_list<T, P>::getMin() const
{
	if (this->empty())
		throw std::logic_error("PriorityQueue_list (exception) - Unable to getMin (empty queue)");

	return queue.read(queue.begin());
}

template<class T, class P>
typename PriorityQueue_list<T, P>::elem PriorityQueue_list<T, P>::getMax() const
{
	if (this->empty())
		throw std::logic_error("PriorityQueue_list (exception) - Unable to getMax (empty queue)");

	return queue.read(queue.endnode());
}

template<class T, class P>
void PriorityQueue_list<T, P>::create()
{
	queue.create();
}

template<class T, class P>
void PriorityQueue_list<T, P>::erasePriorities(const priority& p)
{
	vector<elem> elements;

	//Copy the first queue
	while (!this->empty())
	{
		if ((this->getMin()).getPriority() != p)
			elements.push_back(this->getMin());
		this->pop();
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}
}

template<class T, class P>
void PriorityQueue_list<T, P>::eraseItems(const value_type& i)
{
	vector<elem> elements;

	//Copy the first queue
	while (!this->empty())
	{
		if ( (this->getMin()).getValue() != i)
			elements.push_back(this->getMin());
		this->pop();
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}
}

#endif /* _PQLIST_H_ */
