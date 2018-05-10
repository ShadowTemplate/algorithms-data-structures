#include "set_bool.h"

int main()
{
	Set_bool set;
	set.insert(2);
	set.insert(5);
	set.insert(11);

	Set_bool set2(set);


	Set_bool set3;
	set.erase(5);
	set2.insert(20);

	cout << set;
	cout << set2;


	set3.difference(set2, set);
	cout << set3;





}
