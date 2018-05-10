#include "mfset_set.h"

int main()
{

	Set_pointer<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);
	set.insert(5);

	MFSet_set<int> setTest(set);

	MFSet_set<int> setTest2;
	setTest2.create(set);

	setTest.merge(1, 2);
	setTest.merge(1, 4);
	cout << setTest;

	setTest2.merge(2, 4);
	setTest2.merge(2, 3);
	cout << setTest2;

	if(setTest == setTest2)
		cout << "YES";

	MFSet_set<int> setTest3(setTest2);
	cout << setTest3;
	if(setTest3 == setTest2)
		cout << "YESSIR";
}
