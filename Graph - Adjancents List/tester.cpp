#include "Graph_list.h"

using std::cout;

int main()
{

	Graph_list<int, int> graph;

	Node n0;
	Node n1;
	Node n2;
	Node n3;
	Node n4;
	Node n5;
	Node n6;
	Node n7;
	Node n8;
	Node n9;
	Node n10;

	graph.insNode(n0);
	graph.setLabel(n0, 0);
	graph.insNode(n1);
	graph.setLabel(n1, 1);
	graph.insNode(n2);
	graph.setLabel(n2, 2);
	graph.insNode(n3);
	graph.setLabel(n3, 3);
	graph.insNode(n4);
	graph.setLabel(n4, 4);
	graph.insNode(n5);
	graph.setLabel(n5, 5);
	graph.insNode(n6);
	graph.setLabel(n6, 6);
	graph.insNode(n7);
	graph.setLabel(n7, 7);
	graph.insNode(n8);
	graph.setLabel(n8, 8);
	graph.insNode(n9);
	graph.setLabel(n9, 9);
	graph.insNode(n10);
	graph.setLabel(n10, 10);

	graph.insEdge(n0, n5);
	graph.insEdge(n0, n4);
	graph.insEdge(n0, n1);
	graph.insEdge(n3, n0);
	graph.insEdge(n1, n2);
	graph.insEdge(n2, n1);
	graph.insEdge(n3, n2);
	graph.insEdge(n3, n9);
	graph.insEdge(n2, n6);
	graph.insEdge(n6, n7);
	graph.insEdge(n7, n8);
	graph.insEdge(n8, n7);
	graph.insEdge(n5, n10);

	graph.setWeight(n1, n2, 100);
	graph.setWeight(n7, n8, 200);

	cout << graph;

	if (graph.connectedGraph())
		cout << "Graph is connected" << endl;
	else
		cout << "Graph isn't connected" << endl;

	if (graph.stronglyConnectedGraph())
		cout << "Graph is strongly connected" << endl;
	else
		cout << "Graph isn't strongly connected" << endl;

	if (graph.acyclicGraph())
		cout << "Graph is acyclic" << endl;
	else
		cout << "Graph isn't acyclic" << endl;

	cout << endl << "Path from n0 to n7: " << endl;
	list<Graph_list<int, int>::node> temp = graph.getPath(n0, n7);
	for (list<Graph_list<int, int>::node>::iterator it = temp.begin(); it != temp.end(); it++)
		cout << *it << " ";

	cout << endl << endl << "DFS: " << endl;
	graph.DFS(n0);

	cout << endl << endl;

	cout << "BFS: " << endl;
	graph.BFS(n0);

	cout << endl << endl;

	Graph_list<char, int> graph2;

	Node n11; // A
	Node n12; // B
	Node n13; // C
	Node n14; // D
	Node n15; // F
	Node n16; // G

	graph2.insNode(n11);
	graph2.setLabel(n11, 'A');
	graph2.insNode(n12);
	graph2.setLabel(n12, 'B');
	graph2.insNode(n13);
	graph2.setLabel(n13, 'C');
	graph2.insNode(n14);
	graph2.setLabel(n14, 'D');
	graph2.insNode(n15);
	graph2.setLabel(n15, 'F');
	graph2.insNode(n16);
	graph2.setLabel(n16, 'G');

	graph2.insEdge(n11, n12);
	graph2.setWeight(n11, n12, 2);
	graph2.insEdge(n11, n14);
	graph2.setWeight(n11, n14, 1);
	graph2.insEdge(n12, n14);
	graph2.setWeight(n12, n14, 3);
	graph2.insEdge(n12, n13);
	graph2.setWeight(n12, n13, 3);
	graph2.insEdge(n14, n15);
	graph2.setWeight(n14, n15, 1);
	graph2.insEdge(n15, n13);
	graph2.setWeight(n15, n13, 2);
	graph2.insEdge(n13, n16);
	graph2.setWeight(n13, n16, 2);
	graph2.insEdge(n15, n16);
	graph2.setWeight(n15, n16, 5);

	cout << endl << graph2;

	list<Node> temp2 = graph2.getShortestPath(n11, n16);
	cout << "Shortest path from n11 to n16 is:" << endl;

	for (list<Node>::iterator it = temp2.begin(); it != temp2.end(); it++)
		cout << *it << " ";

	list<Node> temp3 = graph2.adjacentsKLevel(n11, 3);
	cout << endl << endl << "Adjacent nodes of n11 of grade 3:" << endl;

	for (list<Node>::iterator it = temp3.begin(); it != temp3.end(); it++)
		cout << *it << " ";

}
