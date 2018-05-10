#include <iostream>
#include "Graph_matrix.h"

#include <string>
using std::string;

using std::cout;

int main()
{
	/*
	 Graph_matrix<int, int> graph;

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

	 //graph.setWeight(n1, n3, 100);
	 //graph.setWeight(n1, n4, 200);
	 //graph.setLabel(n1, 111);

	 cout << graph;
	 cout << endl;

	 cout << "DFS: ";
	 cout << endl;
	 graph.DFS(n0);

	 cout << endl;
	 cout << endl;

	 cout << "BFS: ";
	 cout << endl;
	 graph.BFS(n0);

	 //	list<Node> temp = graph.getShortestPath(n3, n6);
	 //	cout << "Best path is";
	 //	cout << endl;
	 //	for (list<Node>::iterator it = temp.begin(); it != temp.end(); it++)
	 //		cout << endl << *it;



	 */
	Graph_matrix<char, int> graph;

	Node n0;
	Node n1;
	Node n2;
	Node n3;
	Node n4;
	Node n5;
	Node n6;
	Node n7;
	Node n8;

	graph.insNode(n0);
	graph.setLabel(n0, 'A');
	graph.insNode(n1);
	graph.setLabel(n1, 'B');
	graph.insNode(n2);
	graph.setLabel(n2, 'C');
	graph.insNode(n3);
	graph.setLabel(n3, 'D');
	graph.insNode(n4);
	graph.setLabel(n4, 'E');
	graph.insNode(n5);
	graph.setLabel(n5, 'F');
	graph.insNode(n6);
	graph.setLabel(n6, 'G');
	graph.insNode(n7);
	graph.setLabel(n7, 'H');
	graph.insNode(n8);
	graph.setLabel(n8, 'I');

	graph.insEdge(n0, n1);
	graph.setWeight(n0, n1, 4);
	graph.insEdge(n1, n0);
	graph.setWeight(n1, n0, 4);

	graph.insEdge(n0, n7);
	graph.setWeight(n0, n7, 8);
	graph.insEdge(n7, n0);
	graph.setWeight(n7, n0, 8);

	graph.insEdge(n1, n2);
	graph.setWeight(n1, n2, 8);
	graph.insEdge(n2, n1);
	graph.setWeight(n2, n1, 8);

	graph.insEdge(n1, n7);
	graph.setWeight(n1, n7, 11);
	graph.insEdge(n7, n1);
	graph.setWeight(n7, n1, 11);

	graph.insEdge(n2, n3);
	graph.setWeight(n2, n3, 7);
	graph.insEdge(n3, n2);
	graph.setWeight(n3, n2, 7);

	graph.insEdge(n2, n5);
	graph.setWeight(n2, n5, 4);
	graph.insEdge(n5, n2);
	graph.setWeight(n5, n2, 4);

	graph.insEdge(n2, n8);
	graph.setWeight(n2, n8, 2);
	graph.insEdge(n8, n2);
	graph.setWeight(n8, n2, 2);

	graph.insEdge(n3, n4);
	graph.setWeight(n3, n4, 9);
	graph.insEdge(n4, n3);
	graph.setWeight(n4, n3, 9);

	graph.insEdge(n3, n5);
	graph.setWeight(n3, n5, 14);
	graph.insEdge(n5, n3);
	graph.setWeight(n5, n3, 14);

	graph.insEdge(n4, n5);
	graph.setWeight(n4, n5, 10);
	graph.insEdge(n5, n4);
	graph.setWeight(n5, n4, 10);

	graph.insEdge(n5, n6);
	graph.setWeight(n5, n6, 2);
	graph.insEdge(n6, n5);
	graph.setWeight(n6, n5, 2);

	graph.insEdge(n6, n7);
	graph.setWeight(n6, n7, 1);
	graph.insEdge(n7, n6);
	graph.setWeight(n7, n6, 1);

	graph.insEdge(n6, n8);
	graph.setWeight(n6, n8, 6);
	graph.insEdge(n8, n6);
	graph.setWeight(n8, n6, 6);

	graph.insEdge(n7, n8);
	graph.setWeight(n7, n8, 7);
	graph.insEdge(n8, n7);
	graph.setWeight(n8, n7, 7);

	cout << graph;

//	list<Node> temp = graph.getShortestPath(n0, n5);
//	cout << "Best path is";
//	cout << endl;
//	for (list<Node>::iterator it = temp.begin(); it != temp.end(); it++)
//		cout << endl << *it;

	graph.convertToMST();

	cout << endl << "MST:";
	cout << endl;
	cout << graph;

}
