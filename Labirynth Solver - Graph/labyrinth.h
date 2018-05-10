#ifndef _LABYRINTH_H_
#define _LABYRINTH_H_

#include "Graph_matrix.h"
#include <fstream>

using std::list;
using std::endl;
using std::cout;
using std::ios;
using std::fstream;
using std::vector;

vector<vector<char> > analyzePattern()
{
	fstream f1;
	f1.open("pattern.txt", ios::in); // open the file in read mode

	vector<vector<char> > matrix;

	if (!f1)
		throw std::logic_error("Unable to open pattern.txt");

	vector<char> temp;
	char c;

	while (!f1.eof())
	{
		c = f1.get();
		if (c != '\n' && c != ' ') // ignore blanks
			temp.push_back(c);
		else if (c == '\n')
		{
			matrix.push_back(temp);
			temp.clear();
		}
	}
	f1.close();

	cout << "Pattern acquired: " << endl;
	for (vector<vector<char> >::iterator it = matrix.begin(); it != matrix.end(); it++)
	{
		for (vector<char>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
			cout << *it2;

		cout << endl;
	}
	cout << endl;

	return matrix;
}

vector<vector<int> > convertPatternToID(vector<vector<char> >& matrix, int& counter)
{
	vector<vector<int> > matrixID;

	for (vector<vector<char> >::iterator it = matrix.begin(); it != matrix.end(); it++)
	{
		vector<int> temp;
		for (vector<char>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
		{
			if ((*it2) == '0')
			{
				temp.push_back(counter);
				counter++;
			}
			else
				temp.push_back(-1);
		}
		matrixID.push_back(temp);
		temp.clear();
	}

	cout << "Pattern converted to ID: " << endl;
	for (vector<vector<int> >::iterator it = matrixID.begin(); it != matrixID.end(); it++)
	{
		for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
			cout << *it2 << " ";

		cout << endl;
	}

	cout << endl;

	return matrixID;
}

template<class V, class W>
void buildGraph(Graph_matrix<V, W>& graph, vector<vector<int> > matrixID)
{
	for (vector<vector<int> >::iterator it = matrixID.begin(); it != matrixID.end(); it++)
		for (vector<int>::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
			if ((*it2) != -1)
			{
				Node temp;
				graph.insNode(temp);
				graph.setLabel((graph.nodesList()).back(), (*it2));
			}

	int width = (matrixID.front()).size();
	int height = matrixID.size();

	// now, let's add the edges

	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			if (matrixID[i][j] != -1)
			{
				// check if I've to add an edge towards left
				if (j != 0 && matrixID[i][j - 1] != -1)
				{
					graph.insEdge(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i][j - 1]));
					graph.setWeight(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i][j - 1]), 1);
				}

				// check if I've to add an edge towards right
				if (j != (width - 1) && matrixID[i][j + 1] != -1)
				{
					graph.insEdge(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i][j + 1]));
					graph.setWeight(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i][j + 1]), 1);
				}

				// check if I've to add an edge towards up
				if (i != 0 && matrixID[i - 1][j] != -1)
				{
					graph.insEdge(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i - 1][j]));
					graph.setWeight(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i - 1][j]), 1);
				}

				// check if I've to add an edge towards down
				if (i != (height - 1) && matrixID[i + 1][j] != -1)
				{
					graph.insEdge(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i + 1][j]));
					graph.setWeight(findValue(graph, matrixID[i][j]), findValue(graph, matrixID[i + 1][j]), 1);
				}
			}

//	cout << "The graph has been built:";
//	cout << endl;
//	cout << graph;

}

template<class N, class L, class W>
typename Graph<N, L, W>::node findValue(Graph<N, L, W>& graph, L value)
{
	list<typename Graph<N, L, W>::node> temp = graph.nodesList();

	for (typename list<typename Graph<N, L, W>::node>::iterator it = temp.begin(); it != temp.end(); it++)
		if (graph.getLabel(*it) == value)
			return (*it);

	throw std::logic_error("Unable to retrieve value");
}

void printSolution(Graph_matrix<int, int> graph, list<Graph_matrix<int, int>::node> solution, vector<vector<int> > matrixID)
{
	int width = (matrixID.front()).size();
	int height = matrixID.size();
	bool flag = false;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
			if (matrixID[i][j] == -1)
				cout << "- ";
			else
			{
				for (list<Graph_matrix<int, int>::node>::iterator it = solution.begin();
						(it != solution.end() && !flag); it++)
					if (graph.getLabel((*it)) == matrixID[i][j])
					{
						cout << "X ";
						flag = true;
					}

				if (!flag)
					cout << "0 ";

				flag = false;
			}

		cout << endl;
	}
}

#endif /* _LABYRINTH_H_ */
