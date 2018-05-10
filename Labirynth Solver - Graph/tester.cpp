#include <iostream>
#include "Graph_matrix.h"
#include "labyrinth.h"

/* PRE-CONDITION ON "pattern.txt"
 *
 * Labyrinth must have a rectangular shape;
 * Use - to build the walls;
 * Blanks can be used;
 * Add a \n at the end of the file;
 * Use 0 to indicate a legit tile */


int main()
{
	vector<vector<char> > matrix = analyzePattern();
	int counter = 0; // number of nodes in the graph
	vector<vector<int> > matrixID = convertPatternToID(matrix, counter);
	Graph_matrix<int, int> graph;

	buildGraph(graph, matrixID);

	Graph_matrix<int, int>::node startingNode = findValue(graph, 0);
	Graph_matrix<int, int>::node endingNode = findValue(graph, counter - 1);

	if (graph.isPath(startingNode, endingNode))
	{
		cout << "Labyrinth can be solved." << endl << endl;
		cout << "Please wait, I'm calculating the best solution... ";
		list<Graph_matrix<int, int>::node> solution = graph.getShortestPath(startingNode, endingNode);
		cout << endl << endl << "One possible best solution is (look at X to follow the path):" << endl << endl;
		printSolution(graph, solution, matrixID);
	}
	else
		cout << "Labyrinth can't be solved.";

//	cout << "Press EXIT to quit...";
//	getchar();

}

