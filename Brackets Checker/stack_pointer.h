#ifndef _STACKP_H
#define _STACKP_H

#include <stdexcept>
#include "stack.h"
#include "elemsp.h"

template<class T>
class Stack_pointer: public Stack<T, Element<T>*>
{
public:

	typedef typename Stack<T, Element<T>*>::value_type value_type;
	typedef typename Stack<T, Element<T>*>::position elemp;

	Stack_pointer();
	Stack_pointer(const Stack_pointer<T>&);
	~Stack_pointer();

	Stack_pointer<T>& operator =(const Stack_pointer<T>&);

	void create(); //create the stack
	bool empty() const; // true if the stack is empty
	value_type read() const; //return the top of the stack (don't erase it)
	void push(const value_type&); //add an element to the top of the stack
	void pop(); //erase the first element

private:

	elemp top;
};

template<class T>
Stack_pointer<T>::Stack_pointer()
{
	this->create();
}

template<class T>
Stack_pointer<T>::Stack_pointer(const Stack_pointer<T>& s2)
{
	this->create();
	*this = s2;
}

template<class T>
Stack_pointer<T>::~Stack_pointer()
{
	this->clear();
	top = 0;
}

template<class T>
Stack_pointer<T>& Stack_pointer<T>::operator =(const Stack_pointer<T>& s)
{
	if (&s != this) // avoid auto-assignment.
	{
		this->clear();
		top = 0;

		elemp curr = s.top;
		while (curr->getPrev() != 0)
			curr = curr->getPrev();

		while (curr != 0)
		{
			this->push(curr->getValue());
			curr = curr->getNext();
		}
	}

	return *this;
}

template<class T>
void Stack_pointer<T>::create()
{
	top = 0;
}

template<class T>
bool Stack_pointer<T>::empty() const
{
	return top == 0;
}

template<class T>
typename Stack_pointer<T>::value_type Stack_pointer<T>::read() const
{
	if (this->empty())
		throw std::logic_error("Stack_pointer: exception - Unable to read (empty stack)");

	return top->getValue();
}

template<class T>
void Stack_pointer<T>::push(const value_type& el)
{
	elemp newtop = new Element<value_type>;
	newtop->setValue(el);
	if (top != 0)
	{
		newtop->setPrev(top);
		top->setNext(newtop);
	}
	top = newtop;

}

template<class T>
void Stack_pointer<T>::pop()
{
	if (this->empty())
		throw std::logic_error("Stack_pointer: exception - Unable to pop (empty stack)");

	elemp newtop = top->getPrev();
	delete top;
	top = 0;
	if (newtop != 0)
	{
		top = newtop;
		top->setNext(0);
	}
}

#endif // _STACKP_H
