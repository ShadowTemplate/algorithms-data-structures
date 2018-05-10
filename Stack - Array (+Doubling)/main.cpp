#include "stackvt.h"

int main()
{
	Stack_vector<int> stack1, stack2;

	stack1.push(11);
	stack1.push(6);
	stack1.push(5);
	stack1.push(4);
	stack1.push(9);
	stack1.push(6);
	stack1.push(10);
	stack1.push(3);

	cout << "stack1: " << endl << stack1 << endl;

	stack1.sort();
	cout << "stack1 after 'sort': " << endl << stack1 << endl;

	stack2 = stack1;

	cout << "stack2: " << endl << stack2 << endl;

	if(stack1 == stack2)
		cout << "stack1 = stack2" << endl;
	else
		cout << "stack1 != stack2" << endl;

	stack2.invert();
	cout << endl << "stack2 after 'invert': " << endl << stack2 << endl;

	cout << "stack2 size: " << stack2.size() << endl;

	stack2.pop();
	stack2.pop();
	cout << endl << "stack2 after 2 pop: " << endl << stack2 << endl;

	cout << "new stack2 size: " << stack2.size() << endl;



}
