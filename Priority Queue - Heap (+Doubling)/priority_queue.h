#ifndef _PRIORQUEUE_H_
#define _PRIORQUEUE_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::ostream;
using std::endl;
using std::vector;

template<class E, class P>
class PriorQueue
{
public:
	typedef E elem;
	typedef P priority;

	virtual ~PriorQueue()
	{
	}

	virtual bool empty() const = 0; // true if the tree is empty
	virtual void insert(const elem&) = 0; // insert an element in the queue
	virtual void pop() = 0; // delete the first element having highest priority (for integer: minimum integer = max priority)
	virtual elem getMin() const = 0; // return the the first element with the highest priority (for integer: minimum integer = max priority)
	virtual elem getMax() const = 0; // return the the last element with the lowest priority (for integer: minimum integer = max priority)

	template<class X, class Y>
	friend ostream& operator <<(ostream &, PriorQueue<X, Y>&);

	void clear(); // delete the queue
	bool find(const elem&); // true if the element is present in the list
	int size(); // return the element of the queue
	void join(PriorQueue<E, P>&, PriorQueue<E, P>&); // join two queues: implicit queue must be empty
	void epurateElem(const elem&); // erase from the queue the element
	void changeMin(const elem&); // change the current min with a new element

protected:
	virtual void create() = 0; // create the queue

};

template<class E, class P>
ostream& operator <<(ostream& out, PriorQueue<E, P>& queue)
{
	if (!queue.empty())
	{
		out << "Element (Priority):" << endl;
		vector<E> elements;

		while (!queue.empty())
		{
			elements.push_back(queue.getMin());
			queue.pop();
		}

		for (typename vector<E>::iterator it = elements.begin(); it != elements.end(); it++)
		{
			out << *it;
			out << endl;
			queue.insert(*it);
		}
	}
	else
		out << "Empty Priority Queue" << endl;

	out << endl;
	return out;

}

template<class E, class P>
void PriorQueue<E, P>::clear()
{
	while (!this->empty())
		this->pop();
}

template<class E, class P>
bool PriorQueue<E, P>::find(const elem& el)
{
	if (this->empty())
		return false;

	vector<E> elements;
	bool flag = false;

	while (!this->empty())
	{
		elements.push_back(this->getMin());
		if (this->getMin() == el)
			flag = true;
		this->pop();
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}

	return flag;
}

template<class E, class P>
int PriorQueue<E, P>::size()
{
	vector<E> elements;
	int size = 0;

	while (!this->empty())
	{
		elements.push_back(this->getMin());
		this->pop();
		size++;
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}

	return size;
}

template<class E, class P>
void PriorQueue<E, P>::join(PriorQueue<E, P>& queue1, PriorQueue<E, P>& queue2)
{
	if (!this->empty())
		throw std::logic_error("Priority Queue (exception)");

	vector<E> elements;

	//Copy the first queue
	while (!queue1.empty())
	{
		elements.push_back(queue1.getMin());
		this->insert(queue1.getMin());
		queue1.pop();
	}

	while (!elements.empty())
	{
		queue1.insert(elements.back());
		elements.pop_back();
	}

	//Copy the second queue
	while (!queue2.empty())
	{
		elements.push_back(queue2.getMin());
		this->insert(queue2.getMin());
		queue2.pop();
	}

	while (!elements.empty())
	{
		queue2.insert(elements.back());
		elements.pop_back();
	}
}

template<class E, class P>
void PriorQueue<E, P>::epurateElem(const elem& el)
{
	if (this->find(el))
	{
		vector<E> elements;

		while (!this->empty())
		{
			if (this->getMin() != el)
				elements.push_back(this->getMin());
			this->pop();
		}

		while (!elements.empty())
		{
			this->insert(elements.back());
			elements.pop_back();
		}
	}
}

template<class E, class P>
void PriorQueue<E, P>::changeMin(const elem& el)
{
	if (!this->empty())
		if (el < this->getMin())
		{
			this->pop();
			this->insert(el);
		}
}

#endif /* _PRIORQUEUE_H_ */
