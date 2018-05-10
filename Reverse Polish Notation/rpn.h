#ifndef _RPN_H
#define _RPN_H

#include <string>
#include <iostream>
#include "stack_pointer.h"

using std::cout;
using std::endl;
using std::string;

#define is_operator(c) (c == '+' || c == '-' || c == '/' || c == '*')
#define is_number(c) (c >= '0' && c <= '9')

int op_preced(const char c)
{
	if (c == '*' || c == '/')
		return 2;
	else
		// c == '+' || c == '-'
		return 1;
}

bool RPNConverter(const string input, string& output)
{
	string::const_iterator inputPos = input.begin(); // iterator to the current position of the input string

	char c; // temp buffer

	Stack_pointer<char> stack; // operator stack
	char tempChar; // used for record stack element

	while (inputPos != input.end())
	{
		c = *inputPos; // read one token from the input stream
		if (c != ' ')
		{
			if (is_number(c)) // if it's a number, then add it to output string.
			{
				output.push_back(c);
			}
			else if (is_operator(c)) // if it's an operator
			{
				while (stack.size() > 0)
				{
					tempChar = stack.read();
					// evaluate the priority of the operators
					if (is_operator(tempChar) && (((op_preced(c) <= op_preced(tempChar))) || (op_preced(c) < op_preced(tempChar))))
					{
						stack.pop(); // pop op2 off the stack
						output.push_back(tempChar); // onto the output string
					}
					else
					{
						break;
					}
				}
				stack.push(c); // push op1 onto the stack
			}
			else if (c == '(') // if the token is a left parenthesis, then push it onto the stack
			{
				stack.push(c);
			}
			else if (c == ')') // if the token is a right parenthesis
			{
				bool balancedPar = false;
				// Until the token at the top of the stack is a left parenthesis,
				// pop operators off the stack onto the output string
				while (stack.size() > 0)
				{
					tempChar = stack.read();
					if (tempChar == '(')
					{
						balancedPar = true;
						break;
					}
					else
					{
						output.push_back(tempChar);
						stack.pop();
					}
				}

				if (!balancedPar) // if the stack runs out without finding a left parenthesis there are mismatched parentheses
				{
					cout << "Error: parentheses mismatched" << endl;
					return false;
				}

				stack.pop(); // pop the left parenthesis from the stack, but not onto the output string.
			}
			else
			{
				cout << "Unknown token " << c << endl;
				return false;
			}
		}
		++inputPos;
	}

	// When there are no more tokens to read:
	// While there are still operator tokens in the stack:
	while (stack.size() > 0)
	{
		tempChar = stack.read();
		if (tempChar == '(' || tempChar == ')')
		{
			cout << "Error: parentheses mismatched" << endl;
			return false;
		}
		output.push_back(tempChar);
		stack.pop();
	}

	return true;
}

int calculateRPN(const string input)
{
	Stack_pointer<int> stack;

	string::const_iterator inputPos = input.begin(); // iterator to the current position of the input string

	while (inputPos != input.end())
	{
		if (is_number(*inputPos))
			stack.push(*inputPos - '0');
		else // is an operator
		{
			int op1 = stack.read();
			stack.pop();
			int op2 = stack.read();
			stack.pop();

			if (*inputPos == '+')
				stack.push(op1 + op2);
			else if (*inputPos == '-')
				stack.push(op2 - op1);
			else if (*inputPos == '*')
				stack.push(op2 * op1);
			else if (*inputPos == '/')
				stack.push(op2 / op1);
			else
				throw std::logic_error("Unable to calculate RPN");
		}

		++inputPos;
	}

	if (stack.size() == 1)
		return stack.read();
	else
		throw std::logic_error("Unable to calculate RPN");

	return 0;
}

#endif // _RPN_H
