#include "heap.h"

#include <string>
using std::string;

int main()
{
	Heap<string, int> queue(3);
	Heap<string, int> queue2(3);

	queue.insert("Turing", 2);
	queue.insert("Babbage", 3);
	queue.insert("Dijkstra", 4);
	queue.insert("Chomsky", 3);
	queue.insert("Ada", 7);
	queue.insert(Elem<string, int>("Turing", 5));

	cout << "queue1: " << endl << queue;

	queue2 = queue;

	cout << "queue2: " << endl << queue2;


	if (queue2 == queue)
		cout << "queue2 = queue" << endl;
	else
		cout << "queue2 != queue" << endl;

	cout << endl;

	cout << "queue1 max: " << queue.getMax() << endl;
	cout << "queue1 min: " << queue.getMin() << endl;

	cout << endl;
	queue.eraseItems("Turing");
	queue.erasePriorities(3);
	cout << "queue1: " << endl << queue;

	queue.pop();
	cout << "queue1: " << endl << queue;




}

