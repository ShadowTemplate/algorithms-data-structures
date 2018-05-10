#include "mfset_list.h"

int main()
{
	MFSet_list<int> lol;
	MFSet_list<int> lol2;

	Set_pointer<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);
	set.insert(5);

	lol.create(set);
	lol2.create(set);

	lol.merge(1, 2);
	lol.merge(1, 4);
	cout << lol;

	lol2.merge(2, 4);
	lol2.merge(2, 1);
	cout << lol2;

	if(lol == lol2)
		cout << "YES";

}
