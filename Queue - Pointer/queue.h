#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <vector>

using std::endl;
using std::ostream;
using std::vector;

template<class T, class P>
class Queue
{
public:

	typedef T value_type;
	typedef P position;

	virtual ~Queue()
	{
	}

	virtual void create() = 0; // create the queue
	virtual bool empty() const = 0; // true if the queue is empty
	virtual value_type read() const = 0; // return the first element of the queue (don't erase it)
	virtual void enqueue(const value_type&) = 0; // add an element at the end of the queue
	virtual void dequeue() = 0; // erase the first element of the queue

	bool operator ==(Queue<T, P>&);
	bool operator !=(Queue<T, P>&);

	int size(); // return the number of element in the queue
	void clear(); // erase all the elements
	void invert(); // invert the order of the elements in the queue
	bool find(const value_type); // true if the element is present in the queue
};

template<class T, class P>
ostream& operator <<(ostream& os, Queue<T, P>& currQueue)
{
	vector<T> elements;

	if (currQueue.empty())
		os << "Empty Queue" << endl;
	else
	{
		os << "[ " << currQueue.read();
		elements.push_back(currQueue.read());
		currQueue.dequeue();

		while (!currQueue.empty())
		{
			os << ", " << currQueue.read();
			elements.push_back(currQueue.read());
			currQueue.dequeue();
		}

		os << " ]" << endl;

		for (typename vector<T>::iterator it = elements.begin(); it != elements.end(); it++)
			currQueue.enqueue(*it);
	}

	return os;
}

template<class T, class P>
bool Queue<T, P>::operator ==(Queue<T, P>& q2)
{
	bool flag = true;

	if (this->size() != q2.size())
		return false;

	vector<T> q1elem;
	vector<T> q2elem;

	while (!this->empty())
	{
		if (this->read() != q2.read())
			flag = false;

		q1elem.push_back(this->read());
		this->dequeue();
		q2elem.push_back(q2.read());
		q2.dequeue();
	}

	for (typename vector<T>::iterator it = q1elem.begin(); it != q1elem.end(); it++)
		this->enqueue(*it);

	for (typename vector<T>::iterator it2 = q2elem.begin(); it2 != q2elem.end(); it2++)
		q2.enqueue(*it2);

	return flag;
}

template<class T, class P>
bool Queue<T, P>::operator !=(Queue<T, P>& q2)
{
	return (!(*this == q2));
}

template<class T, class P>
void Queue<T, P>::clear()
{
	while (!this->empty())
		this->dequeue();
}

template<class T, class P>
int Queue<T, P>::size()
{
	if (this->empty())
		return 0;

	int len = 0;
	vector<T> elements;

	while (!this->empty())
	{
		elements.push_back(this->read());
		this->dequeue();
		len++;
	}

	for (int i = 0; i < len; i++)
		this->enqueue(elements[i]);

	return len;
}

template<class T, class P>
void Queue<T, P>::invert()
{
	if (!this->empty())
	{
		vector<value_type> elements;

		while (!this->empty())
		{
			elements.push_back(this->read());
			this->dequeue();
		}

		for (typename vector<value_type>::reverse_iterator it = elements.rbegin(); it != elements.rend(); it++)
			this->enqueue(*it);
	}

}

template<class T, class P>
bool Queue<T, P>::find(const value_type val)
{
	if (!this->empty())
	{
		vector<value_type> elements;
		bool flag = false;

		while (!this->empty())
		{
			if (this->read() == val)
				flag = true;

			elements.push_back(this->read());
			this->dequeue();
		}

		for (typename vector<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
			this->enqueue(*it);

		return flag;
	}

	return false;
}

#endif // _QUEUE_H
