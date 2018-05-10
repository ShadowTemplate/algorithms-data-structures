#include "queuevt.h"

using std::cout;

int main()
{
	Queue_vector<int> Coda;
	Queue_vector<int> Coda2;

	Coda.enqueue(1);
	Coda.enqueue(2);
	Coda.enqueue(3);

	cout << Coda;
	Coda.invert();

	cout << Coda;

}
