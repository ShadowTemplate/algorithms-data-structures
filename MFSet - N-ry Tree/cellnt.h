#ifndef _CELLNT_H
#define _CELLNT_H

template<class T>
class CellNT
{
public:
	typedef T value_type;
	typedef CellNT* node;

	CellNT();
	CellNT(const CellNT<T>&);
	CellNT(const value_type&);
	~CellNT();

	CellNT<T>& operator =(const CellNT<T>&);

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
CellNT<T>::CellNT()
{
	value = value_type();
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
CellNT<T>::CellNT(const CellNT<T>& c2)
{
	*this = c2;
}

template<class T>
CellNT<T>::CellNT(const value_type& val)
{
	value = val;
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
CellNT<T>::~CellNT()
{
	value = value_type();
	father = NULL;
	right = NULL;
	left = NULL;
	child = NULL;
}

template<class T>
CellNT<T>& CellNT<T>::operator =(const CellNT<T>& c2)
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
void CellNT<T>::setValue(const value_type element)
{
	value = element;
}

template<class T>
void CellNT<T>::setFather(node fatherp)
{
	father = fatherp;
}

template<class T>
void CellNT<T>::setRight(node rightp)
{
	right = rightp;
}

template<class T>
void CellNT<T>::setLeft(node leftp)
{
	left = leftp;
}

template<class T>
void CellNT<T>::setChild(node childp)
{
	child = childp;
}

template<class T>
typename CellNT<T>::value_type CellNT<T>::getValue() const
{
	return value;
}

template<class T>
typename CellNT<T>::node CellNT<T>::getFather() const
{
	return father;
}

template<class T>
typename CellNT<T>::node CellNT<T>::getRight() const
{
	return right;
}

template<class T>
typename CellNT<T>::node CellNT<T>::getLeft() const
{
	return left;
}

template<class T>
typename CellNT<T>::node CellNT<T>::getChild() const
{
	return child;
}

#endif // _CELLNT_H
