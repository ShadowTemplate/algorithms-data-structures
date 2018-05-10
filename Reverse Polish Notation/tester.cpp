#include "rpn.h"
#include <fstream>

using std::ios;
using std::fstream;

int main()
{
	string input;

	fstream f1;
	f1.open("infix.txt", ios::in); // open the file in read mode

	if (!f1)
		throw std::logic_error("Unable to open infix.txt");

	char c;
	while (!f1.eof())
	{
		c = f1.get();
		if (c != EOF) // the text isn't completely analysed
			input.push_back(c);
	}
	f1.close();

	cout << "input: " << input << endl;

	string output;

	if (RPNConverter(input, output))
		cout << "output: " << output << endl << endl << "Result: " << calculateRPN(output) << endl;
	else
		cout << "unable to convert input string to RPN" << endl;

}
