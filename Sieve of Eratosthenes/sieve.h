#ifndef _SIEVE_H
#define _SIEVE_H

#include "set_bool.h"

Set_bool sieve(const long unsigned max)
{
	Set_bool prime;
	long unsigned curr = 2; // current number
	long unsigned eraser = 2; // number we are going to erase from the set
	long unsigned counter = 2; // multiplier: x2, x3, x4, x5, ecc...

	// fill the sieve
	for (long unsigned i = 0; i < max; i++)
		prime.insert(i + 1);

	while (curr * curr < max) // the algorithm finish when curr^2 >= max
	{
		while (curr * counter <= max)
		{
			eraser = curr * counter;
			if (prime.find(eraser))
				prime.erase(eraser);
			counter++;
		}
		counter = 2;

		curr++; // find next divisor

		// if the divisor isn't present in the set (it may have been removed previously)
		// we have to find another one
		while (!prime.find(curr) && curr <= max)
			curr++;
	}

	return prime;
}

#endif // _SIEVE_H
