#include "mfset_tree.h"

int main()
{
	Set_pointer<int> set;
	set.insert(1);
	set.insert(2);
	set.insert(3);
	set.insert(4);
	set.insert(5);
	cout << "Starting set: " << set << endl;

	MFSet_tree<int> MFSet1(set);
	cout << "MFSet1: " << MFSet1 << endl;

	MFSet_tree<int> MFSet2;
	MFSet2.create(set);
	cout << "MFSet2: " << MFSet2 << endl;

	MFSet1.merge(1, 2);
	MFSet1.merge(1, 4);
	cout << "MFSet1: " << MFSet1 << endl;

	MFSet2.merge(2, 4);
	MFSet2.merge(2, 3);
	cout << "MFSet2: " << MFSet2 << endl;

	if(MFSet1 == MFSet2)
		cout << "MFSet1 = MFSet2" << endl << endl;
	else
		cout << "MFSet1 != MFSet2" << endl << endl;

	MFSet_tree<int> MFSet3(MFSet2);
	cout << "MFSet3: " << MFSet3 << endl;

	if(MFSet2 == MFSet3)
		cout << "MFSet2 = MFSet3" << endl;
	else
		cout << "MFSet2 != MFSet3" << endl;

}
