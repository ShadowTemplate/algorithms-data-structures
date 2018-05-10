#ifndef _CELLNT_H
#define _CELLNT_H

template<class T>
class Cell
{
public:
	typedef T value_type;
	typedef Cell* node;

	Cell();
	Cell(const Cell<T>&);
	Cell(const value_type&);
	~Cell();

	Cell<T>& operator =(const Cell<T>&);

	void setValue(const value_type);
	value_type getValue() const;
	void setFather(node);
	void setRight(node);
	void setLeft(node);
	void setChild(node);
	node getFather() const;
	node getRight() const;
	node getLeft() const;
	node getChild() const;

private:
	value_type value;
	node father;
	node right; // Right sibling
	node left; // Left sibling
	node child; // First child
};

template<class T>
Cell<T>::Cell()
{
	value = value_type();
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
Cell<T>::Cell(const Cell<T>& c2)
{
	*this = c2;
}

template<class T>
Cell<T>::Cell(const value_type& val)
{
	value = val;
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
Cell<T>::~Cell()
{
	value = value_type();
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
Cell<T>& Cell<T>::operator =(const Cell<T>& c2)
{
	if (&c2 != this) // avoid auto-assignment
	{
		setValue(c2.getValue());
		setLeft(c2.getLeft());
		setRight(c2.getRight());
		setChild(c2.getChild());
	}
	return *this;
}

template<class T>
void Cell<T>::setValue(const value_type element)
{
	value = element;
}

template<class T>
void Cell<T>::setFather(node fatherp)
{
	father = fatherp;
}

template<class T>
void Cell<T>::setRight(node rightp)
{
	right = rightp;
}

template<class T>
void Cell<T>::setLeft(node leftp)
{
	left = leftp;
}

template<class T>
void Cell<T>::setChild(node childp)
{
	child = childp;
}

template<class T>
typename Cell<T>::value_type Cell<T>::getValue() const
{
	return value;
}

template<class T>
typename Cell<T>::node Cell<T>::getFather() const
{
	return father;
}

template<class T>
typename Cell<T>::node Cell<T>::getRight() const
{
	return right;
}

template<class T>
typename Cell<T>::node Cell<T>::getLeft() const
{
	return left;
}

template<class T>
typename Cell<T>::node Cell<T>::getChild() const
{
	return child;
}

#endif // _CELLNT_H
