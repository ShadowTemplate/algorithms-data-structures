#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <stdexcept>
#include "elemdic.h"

template<class K, class I>
class Dictionary
{
public:

	typedef K key;
	typedef I item;

	virtual ~Dictionary()
	{
	}

	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual Element<K, I>* find(const key&) const = 0;
	virtual void insert(const Element<K, I>) = 0;
	virtual void erase(const key&) = 0;
	virtual void modify(const key&, const item&) = 0;

protected:
	virtual void create() = 0;
};

#endif //_DICTIONARY_H
