#include "set_pointerOrd.h"

int main()
{
	Set_pointerOrd<int> set1, set2, set3;

	set1.insert(1);
	set1.insert(2);
	set1.insert(3);
	set1.insert(4);
	set1.insert(5);

	cout << "set1: " << set1 << endl;

	set2 = set1;
	set2.erase(3);
	set2.erase(4);
	set2.insert(7);
	set2.insert(9);

	cout << "set2: " << set2 << endl;

	set3.unionOp(set1, set2);
	cout << "set3 = set1 + set2: " << set3 << endl;
	cout << "set3 size: " << set3.size() << endl << endl;

	set3.clear();
	cout << "clear set3: " << set3 << endl;

	set3.difference(set2, set1);
	cout << "set3 = set2 - set1: " << set3 << endl;

}
