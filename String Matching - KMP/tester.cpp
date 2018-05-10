#include "string_matching.h"

#include <iostream>
#include <fstream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::vector;
using std::ios;
using std::fstream;

int main()
{
	vector<char> pattern; // the pattern we want to search in the text
	vector<char> text; // the text to be searched
	vector<int> table; // required for KMP

	// acquire pattern from file
	fstream f1;
	f1.open("pattern.txt", ios::in); // open the file in read mode
	if (!f1)
		throw std::logic_error("Unable to open pattern.txt");

	while (!f1.eof())
	{
		char c = f1.get();
		if (c != EOF) // the text isn't completely analysed
			pattern.push_back(c);
	}
	f1.close();

	pattern.push_back('\0');
	table.resize(pattern.size());

	// acquire text from file
	f1.open("text.txt", ios::in); // open the file in read mode
	if (!f1)
		throw std::logic_error("Unable to open text.txt");

	while (!f1.eof())
	{
		char c = f1.get();
		if (c != EOF) // the text isn't completely analysed
			text.push_back(c);
	}
	f1.close();

	text.push_back('\0');

	buildTable(table, pattern);

	int firstMatch = KMP(pattern, text, table);

	if (firstMatch == -1)
		cout << "No matching. Pattern isn't present in the text.";
	else
		cout << "First matching starts from position: " << firstMatch;

	cout << endl;

}
