#include "pqlist.h"

#include <string>
using std::string;

int main()
{
//	Heap<string, int> Coda(3);
//	Heap<string, int> Coda2(3);
//
//	Coda.insert("Gianvito", 2);
//	Coda.insert("Francesco", 3);
//	Coda.insert("Mamma", 4);
//	Coda.insert("Papa", 3);
//	Coda.insert("Alessandro", 7);
//	Coda.insert(Elem<string, int>("Daniele", 5));
//
//	cout << "Coda1: " << endl << Coda;
//
//	Coda2 = Coda;
//
//	cout << "Coda2: " << endl << Coda2;
//
//
//	if (Coda2 == Coda)
//		cout << "Equals";
//	else
//		cout << "Different";
	PriorityQueue_list<string, string> Coda;

	Coda.insert("Gianvito", "Natale");
	Coda.insert("Francesco", "Pasqua");
	Coda.insert("Mamma", "A");
	Coda.insert("Papa", "Easter");
	Coda.insert("Alessandro", "LOOOOL");

	cout << Coda;

	PriorityQueue_list<string, int> Queue;

	Queue.insert("Stringa1", 4);
	Queue.insert("Stringa2", 3);
	Queue.insert("Stringa3", 4);
	Queue.insert("Stringa4", 5);
	Queue.insert("Stringa5", 2);

	cout << Queue;
	cout << endl;

	Queue.clear();
	cout << Queue;

}

