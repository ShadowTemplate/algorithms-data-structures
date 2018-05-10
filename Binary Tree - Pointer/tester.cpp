#include "bintree_pointer.h"

int main()
{
	BinTree_pointer<int> t, t2, t3, t4;
	BinTree_pointer<int>::node n = 0, n2 = 0;

	t.ins_root(n);
	n = t.root();
	t.write(n, 1);
	t.ins_right(n);
	n = t.right(n);
	t.write(n, 2);
	n = t.parent(n);
	t.ins_left(n);
	n = t.left(n);
	t.write(n, 3);

	t2.ins_root(n2);
	n2 = t2.root();
	t2.write(n2, 5);
	t2.ins_right(n2);
	n2 = t2.right(n2);
	t2.write(n2, 6);
	n2 = t2.parent(n2);
	t2.ins_left(n2);
	n2 = t2.left(n2);
	t2.write(n2, 7);
	t2.ins_left(n2);
	t2.ins_right(n2);
	n2 = t2.left(n2);
	t2.write(n2, 8);
	n2 = t2.parent(n2);
	n2 = t2.right(n2);
	t2.write(n2, 9);

	cout << "t: " << t << endl;
	;
	cout << "t2: " << t2 << endl;
	;

	t3.build(t, t2);
	cout << "t3: " << t3 << endl;

	t4 = t3;
	cout << "t4: " << t4;
	if (t4 == t3)
		cout << "t4 and t3 are equal" << endl << endl;

	cout << "t3 number of nodes: " << t3.size();
	cout << endl;
	cout << "t3 number of leaves: " << t3.numberLeaves();
	cout << endl;
	cout << "t3 height: " << t3.height();
	cout << endl;
	cout << "t3 number of leaves: " << t3.numberLeaves();
	cout << endl;
	cout << "t3 minimum label: " << t3.min();
	cout << endl;
	cout << "t3 maximum label: " << t3.max();
	cout << endl;

	cout << "t3 preorder visit: ";
	t3.preorder();
	cout << endl;

	cout << "t3 inorder visit: ";
	t3.inorder();
	cout << endl;

	cout << "t3 postorder visit: ";
	t3.postorder();
	cout << endl;

	cout << "t3 breadth visit: ";
	t3.breadth();
	cout << endl;
}
