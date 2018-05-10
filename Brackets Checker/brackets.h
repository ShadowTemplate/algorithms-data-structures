#ifndef _BRACKETS_H
#define _BRACKETS_H

#include "stack_pointer.h"
#include <fstream>

using std::ios;
using std::fstream;

bool checkBrackets()
{
	fstream f1;
	f1.open("brackets.txt", ios::in); // open the file in read mode

	if (!f1)
		throw std::logic_error("Unable to open brackets.txt");

	char c;
	Stack_pointer<char> stack;

	while (!f1.eof())
	{
		c = f1.get();
		if (c != EOF) // the text isn't completely analysed
		{
			if (c == '{' || c == '(')
				stack.push(c);
			else if (c == '}')
			{
				if (stack.empty() || stack.read() != '{')
					return false;

				stack.pop();
			}
			else if (c == ')')
			{
				if (stack.empty() || stack.read() != '(')
					return false;

				stack.pop();
			}
		}
	}
	f1.close();

	if(stack.size() != 0)
		return false;

	return true;
}

#endif // _BRACKETS_H
