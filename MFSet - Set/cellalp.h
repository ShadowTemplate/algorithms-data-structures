#ifndef _CELLPL_H
#define _CELLPL_H

template<class T>
class Cell
{
public:

	typedef Cell* position;
	typedef T value_type;

	Cell();
	Cell(const value_type&, position, position);
	Cell(const Cell<T>&);
	~Cell();

	Cell<T>& operator =(const Cell<T>&);

	void setValue(const value_type);
	value_type getValue() const;
	void setNext(position);
	position getNext() const;
	void setPrev(position);
	position getPrev() const;

private:
	value_type value;
	position prev;
	position next;
};

template<class T>
Cell<T>::Cell()
{
	value = value_type();
	prev = 0;
	next = 0;
}

template<class T>
Cell<T>::Cell(const value_type& element, position nextp = 0, position prevp = 0)
{
	value = element;
	prev = prevp;
	next = nextp;
}

template<class T>
Cell<T>::Cell(const Cell<T>& c2)
{
	*this = c2;
}

template<class T>
Cell<T>::~Cell()
{
	value = value_type();
	prev = 0;
	next = 0;
}

template<class T>
Cell<T>& Cell<T>::operator =(const Cell<T>& c2)
{
	if (this != &c2)
	{
		this->value = c2.value;
		this->prev = c2.prev;
		this->next = c2.next;
	}
}

template<class T>
void Cell<T>::setValue(const value_type element)
{
	value = element;
}

template<class T>
typename Cell<T>::value_type Cell<T>::getValue() const
{
	return value;
}

template<class T>
void Cell<T>::setNext(position nextp)
{
	next = nextp;
}

template<class T>
typename Cell<T>::position Cell<T>::getNext() const
{
	return next;
}

template<class T>
void Cell<T>::setPrev(position prevp)
{
	prev = prevp;
}

template<class T>
typename Cell<T>::position Cell<T>::getPrev() const
{
	return prev;
}

#endif // _CELLPL_H
