#include "listap.h"

#include <string>
using std::string;

int main()
{
	List_pointer<string> list1, list2, list3, list4, list5, list6;

	list1.push_back("Alessandro");
	list1.push_back("Davide");
	list1.push_back("Nicola");
	cout << "List1: " << list1 << endl;

	list2.insOrd("Roberto");
	list2.insOrd("Barbara");
	list2.insOrd("Tiziano");
	list2.insOrd("Gianvito");
	list2.insOrd("Nicola");
	cout << "List2: " << list2 << endl;

	list3.merge(list1, list2);
	cout << "List3: " << list3 << endl;

	list4.join(list1, list2);
	cout << "List4: " << list4 << endl;

	if (list3 == list4)
		cout << "List3 = List4" << endl;
	else
		cout << "List3 != List4" << endl;

	cout << endl << "Sorting List4..." << endl;
	list4.sort();
	cout << "List4: " << list4 << endl;

	if (list3 == list4)
		cout << "List3 = List4" << endl;
	else
		cout << "List3 != List4" << endl;

	cout << endl;

	list5.insOrd("Barbara");
	list5.insOrd("Tiziano");
	list5.insOrd("Gianvito");
	list5.insOrd("Mauro");
	list5.insOrd("Stefano");
	cout << "List5: " << list5 << endl;

	cout << "List6 = elements in common between List2 e List5" << endl;
	list6.common(list2, list5);
	cout << "List6: " << list6 << endl;

}
