#include "hash_table.h"

int main()
{
	Hash_table<string, int> dic(1), dic2(1), dic3;

	dic.insert(Element<string, int>("BABBAGE", 2));
	dic.insert(Element<string, int>("TURING", 3));
	dic.insert(Element<string, int>("PASCAL", 5));
	dic.insert(Element<string, int>("ADA", 20));

	cout << "dic:" << endl << dic;

	dic.erase("BABBAGE");
	dic.erase("ADA");

	cout << "dic:" << endl << dic;

	dic2.insert(Element<string, int>("Stringa1", 20));
	dic2.insert(Element<string, int>("Stringa2", 35));

	cout << "dic2:" << endl << dic2;

	dic2 = dic;
	cout << "dic2:" << endl << dic2;

	if(dic == dic2)
		cout << "dic = dic2" << endl;
	else
		cout << "dic != dic2" << endl;

	dic2.modify("PASCAL", 10);

	cout << endl << "After changing dic2: ";

	if(dic == dic2)
		cout << "dic = dic2" << endl;
	else
		cout << "dic != dic2" << endl;

	cout << endl;

	dic3.insert(Element<string, int>("Stringa1", 20));
	dic3.insert(Element<string, int>("Stringa2", 35));
	cout << "dic3:" << endl << dic3;

	dic.join(dic3);
	cout << "dic:" << endl << dic;

}
