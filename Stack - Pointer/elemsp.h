#ifndef _ELEMSP_H
#define _ELEMSP_H

template<class T>
class Element
{
public:

	typedef T value_type;
	typedef Element* elemp;

	Element();
	Element(const value_type&);
	~Element();

	Element<T>& operator =(const Element<T>&);
	bool operator ==(const Element<T>&) const;
	bool operator !=(const Element<T>&) const;

	void setValue(const value_type);
	value_type getValue() const;
	void setPrev(elemp);
	void setNext(elemp);
	elemp getPrev() const;
	elemp getNext() const;

private:
	value_type value;
	elemp prev;
	elemp next;
};

template<class T>
Element<T>::Element()
{
	value = value_type();
	prev = 0;
	next = 0;
}

template<class T>
Element<T>::Element(const value_type& val)
{
	value = val;
	prev = 0;
	next = 0;
}

template<class T>
Element<T>::~Element()
{
	value = value_type();
	prev = 0;
	next = 0;
}

template<class T>
Element<T>& Element<T>::operator =(const Element<T>& c2)
{
	if (&c2 != this) // avoid auto-assignment
	{
		this->setValue(c2.getValue());
		this->setPrev(c2.getPrev());
		this->setNext(c2.getNext());
	}
	return *this;
}

template<class T>
bool Element<T>::operator ==(const Element<T>& c2) const
{
	if (this->value != c2.value)
		return false;
	if (this->prev != c2.prev)
		return false;
	if (this->next != c2.next)
		return false;

	return true;
}

template<class T>
bool Element<T>::operator !=(const Element<T>& c2) const
{
	return (!(c2 == *this));
}

template<class T>
void Element<T>::setValue(const value_type element)
{
	value = element;
}

template<class T>
typename Element<T>::value_type Element<T>::getValue() const
{
	return value;
}

template<class T>
void Element<T>::setPrev(elemp prevp)
{
	prev = prevp;
}

template<class T>
void Element<T>::setNext(elemp nextp)
{
	next = nextp;
}

template<class T>
typename Element<T>::elemp Element<T>::getPrev() const
{
	return prev;
}

template<class T>
typename Element<T>::elemp Element<T>::getNext() const
{
	return next;
}

#endif // _ELEMSP_H
