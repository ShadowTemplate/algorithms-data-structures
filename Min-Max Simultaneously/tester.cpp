#include <iostream>
#include "minmax.h"

using std::cout;
using std::endl;

const unsigned int maxsize = 9;

int main()
{
	int array[maxsize];

	array[0] = 7;
	array[1] = 9;
	array[2] = 6;
	array[3] = 4;
	array[4] = 5;
	array[5] = 3;
	array[6] = 1;
	array[7] = 8;
	array[8] = 2;

	Pair<int> values = minMAX(array, 0, maxsize-1);

	cout << "min: " << values.min << endl;

	cout << "MAX: " << values.max << endl;

}
