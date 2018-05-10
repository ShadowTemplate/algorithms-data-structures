#ifndef _ELEMDIC_H
#define _ELEMDIC_H

#include <iostream>

using std::ostream;

template<class K, class I>
class Element
{
public:
	typedef K key;
	typedef I item;

	Element();
	Element(const key&, const item&);
	Element(const Element<K, I>&);
	~Element();

	Element<K, I>& operator =(const Element<K, I>&);

	bool operator ==(const Element<K, I>&) const;
	bool operator !=(const Element<K, I>&) const;

	void setKey(const key&);
	void setItem(const item&);
	key getKey() const;
	item getItem() const;

private:
	key valueKey;
	item value;
};

template<class K, class I>
ostream& operator <<(ostream& os, const Element<K, I>& el)
{
	os << "Key: " << el.getKey() << " // " << "Value: " << el.getItem();
	return os;
}

template<class K, class I>
Element<K, I>::Element()
{
	valueKey = key();
	value = item();
}

template<class K, class I>
Element<K, I>::Element(const key& k, const item& val)
{
	valueKey = k;
	value = val;
}

template<class K, class I>
Element<K, I>::Element(const Element<K, I>& el2)
{
	*this = el2;
}

template<class K, class I>
Element<K, I>::~Element()
{
	valueKey = key();
	value = item();
}

template<class K, class I>
Element<K, I>& Element<K, I>::operator =(const Element<K, I>& el2)
{
	if (&el2 != this) // avoid auto-assignment
	{
		this->setItem(el2.getItem());
		this->setKey(el2.getKey());
	}
	return *this;
}

template<class K, class I>
bool Element<K, I>::operator ==(const Element<K, I>& el2) const
{
	if((this->valueKey == el2.valueKey) && (this->value == el2.value))
		return true;

	return false;
}

template<class K, class I>
bool Element<K, I>::operator !=(const Element<K, I>& el2) const
{
	return(!(*this==el2));
}

template<class K, class I>
void Element<K, I>::setKey(const key& k)
{
	valueKey = k;
}

template<class K, class I>
void Element<K, I>::setItem(const item& k)
{
	value = k;
}

template<class K, class I>
typename Element<K, I>::key Element<K, I>::getKey() const
{
	return valueKey;
}

template<class K, class I>
typename Element<K, I>::item Element<K, I>::getItem() const
{
	return value;
}

#endif //_ELEMDIC_H
