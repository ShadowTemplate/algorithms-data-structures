#include "sieve.h"

int main()
{
	long unsigned max = 1000; // up to 4700 ca.
	Set_bool primeNumbers;

	primeNumbers = sieve(max);

	cout << primeNumbers;
	cout << "Elements found: " << primeNumbers.size();
}
