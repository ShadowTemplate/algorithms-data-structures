#ifndef _BAG_H
#define _BAG_H

#include "N-aryTree_pointer.h"
#include "Item.h"

template<class T, class N>
class Bag
{
public:

	typedef T value_type;
	typedef N weight_type;

	Bag();
	Bag(const Bag<T, N>&);
	~Bag();

	Bag<T, N>& operator =(const Bag<T, N>&);

	NaryTree_pointer<Item<T, N> > config;
	weight_type maxWeight;
	value_type maxSum;

};

template<class T, class N>
Bag<T, N>::Bag()
{
	Cell<Item<T, N> > emptyItem;
	config.ins_root(&emptyItem);
	maxWeight = weight_type();
	maxSum = value_type();
}

template<class T, class N>
Bag<T, N>::Bag(const Bag<T, N>& bag2)
{
	*this = bag2;
}

template<class T, class N>
Bag<T, N>::~Bag()
{
	if (!config.empty())
		config.erase(config.root());

	maxWeight = weight_type();
	maxSum = value_type();
}

template<class T, class N>
Bag<T, N>& Bag<T, N>::operator =(const Bag<T, N>& bag)
{
	if (&bag != this) // avoid auto-assignment
	{
		config = bag.config;
		maxWeight = bag.maxWeight;
		maxSum = bag.maxSum;
	}
	return *this;
}

#endif // _BAG_H
