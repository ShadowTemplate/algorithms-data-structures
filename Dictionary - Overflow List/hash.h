#ifndef _HASHFUN_H
#define _HASHFUN_H

#include <string>
using std::string;

template<class T>
class Hash
{
public:

	typedef T type;

	unsigned int operator()(const type the_key) const
	{
		unsigned long hash_value = 0;

		hash_value = (unsigned int) sizeof(the_key);
		return (unsigned int) (hash_value);
	}
};

template<>
class Hash<string>
{
public:
	unsigned int operator()(const string str) const
	{
		// a bitwise hash function written by Justin Sobel
		unsigned int b = 378551;
		unsigned int a = 63689;
		unsigned int hash = 0;

		for (std::size_t i = 0; i < str.length(); i++)
		{
			hash = hash * a + str[i];
			a = a * b;
		}

		return hash;
	}
};

template<>
class Hash<int>
{
public:
	unsigned int operator()(const int key) const
	{
		// middle-square method of hashing
		unsigned int const exp = 10; // Mb = 1024 = 2^10
		unsigned int const k = 8 * sizeof(unsigned int);

		return ((key * key) >> (k - exp));
	}
};

template<>
class Hash<char>
{
public:
	unsigned int operator()(const char key) const
	{
		// middle-square method of hashing
		unsigned int const exp = 10; // Mb = 1024 = 2^10
		unsigned int const k = 8 * sizeof(unsigned int);
		unsigned int elem = (unsigned int) key;

		return ((elem * elem) >> (k - exp));
	}
};

#endif // _HASHFUN_H
