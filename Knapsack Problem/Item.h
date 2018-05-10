#ifndef _BAGITEM_H
#define _BAGITEM_H

#include <string>
using std::string;

template<class T, class N>
class Item
{
public:
	typedef T value_type;
	typedef N weight_type;

	string name;
	value_type value;
	weight_type weight;
	int ID;

	Item();
	Item(const Item<T, N>&);
	~Item();

	Item<T, N>& operator =(const Item<T, N>&);
	bool operator ==(const Item<T, N>&) const;
	bool operator !=(const Item<T, N>&) const;

	bool operator <(const Item<T, N>&) const; // useful for greedy (to sort items)
};

template<class T, class N>
ostream& operator <<(ostream& out, const Item<T, N>& item)
{
	out << "Name: " << item.name << " - Value: " << item.value << " - Weight: " << item.weight << " - ID: " << item.ID;
	return out;
}

template<class T, class N>
Item<T, N>::Item()
{
	name = string();
	value = value_type();
	weight = weight_type();
	ID = 0;
}

template<class T, class N>
Item<T, N>::Item(const Item<T, N>& item2)
{
	*this = item2;
}

template<class T, class N>
Item<T, N>::~Item()
{
	name = string();
	value = value_type();
	weight = weight_type();
	ID = 0;
}

template<class T, class N>
Item<T, N>& Item<T, N>::operator =(const Item<T, N>& item2)
{
	if (&item2 != this) // avoid auto-assignment
	{
		name = item2.name;
		value = item2.value;
		weight = item2.weight;
		ID = item2.ID;
	}
	return *this;
}

template<class T, class N>
bool Item<T, N>::operator ==(const Item<T, N>& i2) const
{
	if (name != i2.name)
		return false;
	if (value != i2.value)
		return false;
	if (weight != i2.weight)
		return false;
	if (ID != i2.ID)
		return false;

	return true;
}

template<class T, class N>
bool Item<T, N>::operator !=(const Item<T, N>& i2) const
{
	return (!(*this == i2));
}

template<class T, class N>
bool Item<T, N>::operator <(const Item<T, N>& i2) const
{
	return !((this->value / this->weight) < (i2.value / i2.weight));
}

#endif // _BAGITEM_H
