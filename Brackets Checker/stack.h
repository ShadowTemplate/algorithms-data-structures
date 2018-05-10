#ifndef _STACK_H
#define _STACK_H

#include <iostream>
#include <deque>

using std::cout;
using std::endl;
using std::ostream;
using std::deque;

template<class T, class N>
class Stack
{
public:

	typedef T value_type;
	typedef N position;

	virtual ~Stack()
	{
	}

	virtual void create() = 0; //create the stack
	virtual bool empty() const = 0; // true if the stack is empty
	virtual value_type read() const = 0; //return the top of the stack (don't erase it)
	virtual void push(const value_type&) = 0; //add an element to the top of the stack
	virtual void pop() = 0; //erase the first element

	bool operator ==(Stack<value_type, position>&);
	bool operator !=(Stack<value_type, position>&);

	int size(); // returns the number of element in the stack
	void clear(); // erases all the elements
	void invert(); // invert the order of the elements in the stack
	bool find(const value_type); // true if the element is present in the stack
	void sort(); // sort the elements: smallest at the top

};

template<class T, class N>
ostream& operator <<(ostream& os, Stack<T, N>& currstack)
{
	deque<T> elements;

	if (currstack.empty())
		os << "Empty Stack" << endl;
	else
	{
		os << "Top -> [ " << currstack.read();
		elements.push_back(currstack.read());
		currstack.pop();

		while (!currstack.empty())
		{
			os << ", " << currstack.read();
			elements.push_back(currstack.read());
			currstack.pop();
		}

		os << " ] <- Bottom" << endl;

		for (typename std::deque<T>::const_reverse_iterator it = elements.rbegin(); it != elements.rend(); it++)
			currstack.push(*it);
	}

	return os;
}

template<class T, class N>
bool Stack<T, N>::operator ==(Stack<T, N>& s2)
{
	bool flag = true;

	if (this->size() != s2.size())
		return false;

	deque<value_type> s1elem;
	deque<value_type> s2elem;

	while (!this->empty())
	{
		if (this->read() != s2.read())
			flag = false;

		s1elem.push_back(this->read());
		this->pop();
		s2elem.push_back(s2.read());
		s2.pop();
	}

	for (typename std::deque<value_type>::const_reverse_iterator it = s1elem.rbegin(); it != s1elem.rend(); it++)
		this->push(*it);

	for (typename std::deque<value_type>::const_reverse_iterator it2 = s2elem.rbegin(); it2 != s2elem.rend();
			it2++)
		s2.push(*it2);

	return flag;
}

template<class T, class N>
bool Stack<T, N>::operator !=(Stack<T, N>& s2)
{
	return (!(*this == s2));
}

template<class T, class N>
void Stack<T, N>::clear()
{
	while (!this->empty())
		this->pop();
}

template<class T, class N>
int Stack<T, N>::size()
{
	if (this->empty())
		return 0;

	int len = 0;
	deque<value_type> elements;

	while (!this->empty())
	{
		elements.push_back(this->read());
		this->pop();
		len++;
	}

	for (typename std::deque<value_type>::const_reverse_iterator it = elements.rbegin(); it != elements.rend();
			it++)
		this->push(*it);

	return len;
}

template<class T, class N>
void Stack<T, N>::invert()
{
	if (!this->empty())
	{
		deque<value_type> elements;

		while (!this->empty())
		{
			elements.push_back(this->read());
			this->pop();
		}

		for (typename deque<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
			this->push(*it);
	}

}

template<class T, class N>
bool Stack<T, N>::find(const value_type val)
{
	if (!this->empty())
	{
		deque<value_type> elements;
		bool flag = false;

		while (flag == false && !this->empty())
		{
			if (this->read() == val)
				flag = true;

			elements.push_front(this->read());
			this->pop();
		}

		for (typename deque<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
			this->push(*it);

		return flag;
	}

	return false;
}

template<class T, class N>
void Stack<T, N>::sort()
{
	if (!this->empty())
	{
		int stackSize = this->size();
		value_type *elements = new value_type[stackSize];
		int i = 0, j = 0, imin = 0;
		value_type tempValue;

		while (!this->empty())
		{
			elements[i] = this->read();
			this->pop();
			i++;
		}

		//Selection sort of the array
		for (i = 0; i < stackSize - 1; i++)
		{
			imin = i;
			for (j = i + 1; j < stackSize; j++)
			{
				if (elements[j] < elements[imin])
					imin = j;
			}

			tempValue = elements[i];
			elements[i] = elements[imin];
			elements[imin] = tempValue;
		}

		// Insert element in the stack (first the greatest )
		for (i = 0; i < stackSize; i++)
			this->push(elements[stackSize - 1 - i]);
	}
}

#endif // _STACK_H
