#ifndef _CELLBST_H
#define _CELLBST_H

template<class T>
class Cell
{
public:

	typedef T value_type;
	typedef Cell* node;

	Cell();
	Cell(const value_type&);
	~Cell();

	Cell<T>& operator =(const Cell<T>&);
	bool operator ==(const Cell<T>&) const;
	bool operator !=(const Cell<T>&) const;

	void setValue(const value_type);
	value_type getValue() const;
	void setFather(node);
	void setRight(node);
	void setLeft(node);
	node getFather() const;
	node getRight() const;
	node getLeft() const;

private:
	value_type value;
	node father;
	node right;
	node left;
};

template<class T>
Cell<T>::Cell()
{
	value = value_type();
	father = 0;
	right = 0;
	left = 0;
}

template<class T>
Cell<T>::Cell(const value_type& val)
{
	value = val;
	father = 0;
	right = 0;
	left = 0;
}

template<class T>
Cell<T>::~Cell()
{
	value = value_type();
	father = 0;
	right = 0;
	left = 0;
}

template<class T>
Cell<T>& Cell<T>::operator =(const Cell<T>& c2)
{
	if (&c2 != this) // avoid auto-assignment
	{
		this->setValue(c2.getValue());
		this->setFather(c2.getFather());
		this->setLeft(c2.getLeft());
		this->setRight(c2.getRight());
	}
	return *this;
}

template<class T>
bool Cell<T>::operator ==(const Cell<T>& c2) const
{
	if (this->value != c2.value)
		return false;
	if (this->father != c2.father)
		return false;
	if (this->right != c2.right)
		return false;
	if (this->left != c2.left)
		return false;

	return true;
}

template<class T>
bool Cell<T>::operator !=(const Cell<T>& c2) const
{
	return (!(c2 == *this));
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

#endif // _CELLBST_H
