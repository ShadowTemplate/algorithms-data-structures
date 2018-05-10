#ifndef _STRINGMATCHING_H
#define _STRINGMATCHING_H

#include <vector>
using std::vector;

void buildTable(vector<int>& Table, vector<char> Pattern)
{
	int pos = 2;
	int index = 0; // index starting from 0 in pattern of the next char of the candidate substring

	Table[0] = -1;
	Table[1] = 0;

	while (pos < (int) Pattern.size())
	{
		if (Pattern[pos - 1] == Pattern[index])
		{
			Table[pos] = index + 1;
			pos++;
			index++;
		}
		else if (index > 0)
		{
			index = Table[index];
		}
		else
		{
			Table[pos] = 0;
			pos++;
		}
	}
}

int KMP(vector<char> Pattern, vector<char> Text, vector<int> Table)
{
	int m = 0; // current position in the text
	int i = 0; // current position in the pattern (char that will be checked)

	while (Text[m + i] != '\0' && Pattern[i] != '\0')
		if (Text[m + i] == Pattern[i])
			++i;
		else
		{
			m += i - Table[i];
			if (i > 0)
				i = Table[i];
		}

	if (Pattern[i] == '\0')
		return m;
	else
		return -1;
}

#endif // _STRINGMATCHING_H
