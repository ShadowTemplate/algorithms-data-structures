#include <iostream>
#include "nms.h"

using std::cout;
using std::endl;

int main()
{
	list<int> l1;

	l1.push_back(10);
	l1.push_back(2);
	l1.push_back(5);
	l1.push_back(3);
	l1.push_back(7);
	l1.push_back(9);
	l1.push_back(4);
	l1.push_back(1);

	cout << "list: " << endl;
	for (list<int>::iterator it = l1.begin(); it != l1.end(); it++)
		cout << *it << " ";

	NMS(l1);

	cout << endl << "After NMS: " << endl;
	for (list<int>::iterator it = l1.begin(); it != l1.end(); it++)
		cout << *it << " ";

}
