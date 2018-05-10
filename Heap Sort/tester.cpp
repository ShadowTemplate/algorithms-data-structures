#include "heapsort.h"

int main()
{
	char array[10];

	array[0] = 'a';
	array[1] = 'b';
	array[2] = 'f';
	array[3] = 'j';
	array[4] = 'z';
	array[5] = 'g';
	array[6] = 'l';
	array[7] = 'a';
	array[8] = 'n';
	array[9] = 'e';

	for(int i = 0; i < 10; i++)
		cout << array[i] << " ";

	heapSort(array, 10);

	cout << endl;

	for(int i = 0; i < 10; i++)
		cout << array[i] << " ";

}

