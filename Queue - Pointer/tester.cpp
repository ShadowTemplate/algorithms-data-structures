#include "queue_pointer.h"

using std::cout;

int main()
{
	Queue_pointer<int> queue1, queue2;

	queue1.enqueue(1);
	queue1.enqueue(2);
	queue1.enqueue(3);
	queue1.enqueue(4);
	queue1.enqueue(5);
	queue1.enqueue(6);
	queue1.enqueue(7);

	cout << "queue1: " << queue1 << endl;

	if (queue1.find(9))
		cout << "9 present in queue1" << endl;
	else
		cout << "9 not present in queue1" << endl;

	queue2 = queue1;

	cout << endl << "queue2: " << queue2 << endl;

	if (queue2 == queue1)
		cout << "queue2 = queue1" << endl;
	else
		cout << "queue2 != queue1" << endl;

	queue2.enqueue(9);

	cout << endl << "queue2: " << queue2 << endl;

	if (queue2.find(9))
		cout << "9 present in queue2" << endl;
	else
		cout << "9 not present in queue2" << endl;

	cout << endl;

	if (queue2 == queue1)
		cout << "queue2 = queue1" << endl;
	else
		cout << "queue2 != queue1" << endl;

	queue2.invert();
	cout << endl << "queue2 after 'invert': " << queue2 << endl;

}
