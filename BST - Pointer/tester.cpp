#include "BST_pointer.h"
#include <iostream>

int main()
{
	BST_pointer<int> t1;

	t1.insert(20);
	t1.insert(15);
	t1.insert(30);
	t1.insert(12);
	t1.insert(18);
	t1.insert(17);
	t1.insert(28);
	t1.insert(32);

	cout << t1 << endl;

	t1.erase(17);

	cout << t1 << endl;

	t1.erase(15);

	cout << t1 << endl;

}
