#include "Graph_matrix.h"
#include "graph_colouring.h"

int main()
{
	Graph_matrix<colour, int> graph;
	Palette palette(4);

	palette.addColour("Red");
	palette.addColour("Green");
	palette.addColour("Blue");
	palette.addColour("Yellow");

	Node n0;
	Node n1;
	Node n2;
	Node n3;
	Node n4;
	Node n5;

	graph.insNode(n0);
	graph.insNode(n1);
	graph.insNode(n2);
	graph.insNode(n3);
	graph.insNode(n4);
	graph.insNode(n5);

	graph.insEdge(n0, n1);
	graph.insEdge(n1, n0);

	graph.insEdge(n0, n2);
	graph.insEdge(n2, n0);

	graph.insEdge(n0, n3);
	graph.insEdge(n3, n0);

	graph.insEdge(n0, n4);
	graph.insEdge(n4, n0);

	graph.insEdge(n0, n5);
	graph.insEdge(n5, n0);

	graph.insEdge(n1, n2);
	graph.insEdge(n2, n1);

	graph.insEdge(n1, n3);
	graph.insEdge(n3, n1);

	graph.insEdge(n2, n3);
	graph.insEdge(n3, n2);

	graph.insEdge(n2, n4);
	graph.insEdge(n4, n2);

	graph.insEdge(n2, n5);
	graph.insEdge(n5, n2);

	graph.insEdge(n3, n4);
	graph.insEdge(n4, n3);

	graph.insEdge(n4, n5);
	graph.insEdge(n5, n4);

	cout << graph;

	graphColour(graph, palette, n0);

	cout << "After algorithm: " << endl << graph;
}
