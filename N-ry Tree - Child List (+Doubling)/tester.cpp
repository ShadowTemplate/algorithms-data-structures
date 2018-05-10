#include <iostream>
#include "N-aryTree_childList.h"

int main()
{

	NaryTree_childList<int> t1, t2, t3, t4, t5;
	NaryTree_childList<int>::node n1 = 0, n2 = 0, n3 = 0;

	t1.ins_root(n1);
	n1 = t1.root();
	t1.write(n1, 1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 2);
	n1 = t1.parent(n1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 3);
	n1 = t1.parent(n1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 4);
	n1 = t1.parent(n1);
	n1 = t1.firstChild(n1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 6);
	n1 = t1.parent(n1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 11);
	n1 = t1.parent(n1);
	t1.insLastChild(n1);
	n1 = t1.lastChild(n1);
	t1.write(n1, 7);

	t2.ins_root(n2);
	n2 = t2.root();
	t2.write(n2, 5);
	t2.insLastChild(n2);
	n2 = t2.lastChild(n2);
	t2.write(n2, 9);
	n2 = t2.parent(n2);
	t2.insLastChild(n2);
	n2 = t2.lastChild(n2);
	t2.write(n2, 20);
	n2 = t2.parent(n2);
	t2.insLastChild(n2);
	n2 = t2.lastChild(n2);
	t2.write(n2, 10);
	n2 = t2.parent(n2);
	n2 = t2.firstChild(n2);
	t2.insLastChild(n2);
	n2 = t2.lastChild(n2);
	t2.write(n2, 6);

	t3.ins_root(n3);
	n3 = t3.root();
	t3.write(n3, 1);
	t3.insLastChild(n3);
	n3 = t3.lastChild(n3);
	t3.write(n3, 2);
	n3 = t3.parent(n3);
	t3.insLastChild(n3);
	n3 = t3.lastChild(n3);
	t3.write(n3, 3);
	t3.insRightSibling(n3);
	n3 = t3.parent(n3);
	n3 = t3.lastChild(n3);
	t3.write(n3, 4);
	n3 = t3.parent(n3);
	n3 = t3.firstChild(n3);
	t3.insRightSibling(n3);
	n3 = t3.nextSibling(n3);
	t3.write(n3, 6);

	t4 = t3;
	t4 = t2;

	cout << "T1 " << t1 << endl;

	cout << "T2 " << t2 << endl;

	cout << "T3 " << t3 << endl;

	cout << "T4 " << t4 << endl;

	t5.build(t4, t3);

	cout << "T5 " << t5 << endl;

	cout << "T5 height: " << t5.height() << endl;

	cout << "T5 grade: " << t5.gradeN() << endl;

	cout << "T5 max label: " << t5.max() << endl;

	cout << endl;

	if (t4 == t2)
		cout << "T4 = T2" << endl;
	else
		cout << "T4 != T2" << endl;

}
