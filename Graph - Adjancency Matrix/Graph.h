#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "edge.h"
#include "set_pointer.h"
#include "mfset_set.h"

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <climits>

using std::list;
using std::queue;
using std::vector;
using std::endl;
using std::ostream;
using std::cout;

template<class N, class L, class W>
class Graph
{
public:
	typedef N node;
	typedef L label;
	typedef W weight;

	virtual ~Graph()
	{
	}

	virtual void create() = 0;
	virtual bool empty() const = 0;
	virtual void insNode(node&) = 0;
	virtual void insEdge(const node, const node) = 0;
	virtual bool isNode(const node) const = 0;
	virtual bool isEdge(const node, const node) const = 0;
	virtual void eraseNode(const node) = 0;
	virtual void eraseEdge(const node, const node) = 0;
	virtual list<node> adjacents(const node) const = 0;
	virtual list<node> nodesList() const = 0;
	virtual label getLabel(const node) const = 0;
	virtual void setLabel(const node, const label) = 0;
	virtual weight getWeight(const node, const node) const = 0;
	virtual void setWeight(const node, const node, const weight) = 0;

	int numNodes() const; // number of the nodes in the graph
	int numEdges() const; // number of edges in the graph
	bool completeGraph() const; // true if every node is directly linked with all the others (in both directions)
	bool connectedGraph() const; // true if for every pair of node (u,j) there is a path from u to j or from j to u
	bool stronglyConnectedGraph() const; // true if for every pair of node (u,j) there is a path from u to j and from j to u
	int inGrade(const node) const; // number of edges starting from the node
	int outGrade(const node) const; // number of edges ending in the node
	bool linked(const node) const; // true if the node has at least one edge (from or to the node)
	list<node> daisyChained(const node) const; // list of the nodes reachable with a path starting from the node
	bool isLoopNode(const node) const; // true if the node is present in its list of reachable nodes
	bool acyclicGraph() const; // true if every node isn't a loopNode
	list<node> adjacentsKLevel(const node, const int) const; // list of nodes reachable with K edges from the node
	bool isPath(const node, const node) const; // true if there is a path from the starting node to the ending
	bool isNewPath(const node, const node, const list<node>) const; // true if there is a path from the starting node to the ending that avoids nodes in the list
	list<node> getPath(const node, const node) const; // return a list of nodes: together they are a path between the two nodes
	void DFS(const node) const;
	void BFS(const node) const;
	vector<edge<N, W> > shortestPath(const node) const; // return a vector of edges by which is possible to create the shortest paths
	list<node> getShortestPath(const node, const node) const; // return a list of nodes: together they are the best path between the two nodes
	void clearEdges(); // erase all the edges of the graph
	list<edge<N, W> > edgesList() const; // return a list of all the edges of the graph
	Set_pointer<edge<N,W> > MST(); // return the set of edges of the MST
	void convertToMST(); // convert a graph to its MST

private:
	void DFS(const node, list<node>&) const;
	weight pathDistance(const node, const vector<edge<N, W> >) const; // return the current shortest distance to the node
	void setFatherPath(const node, const node, vector<edge<N, W> >&) const; // set the second node as the "father" of the first
	void setWeightPath(const node, const weight, vector<edge<N, W> >&) const; // set the weight in the edge ending in the node
};

template<class N, class L, class W>
ostream& operator <<(ostream& out, const Graph<N, L, W>& graph)
{
	if (!graph.empty())
	{
		out << "Label [ID]: Adjacent1 [ID1] (Weight1) // Adjacent2 [ID2] (Weight2) // ... //" << endl;

		list<typename Graph<N, L, W>::node> temp = graph.nodesList();
		for (typename list<typename Graph<N, L, W>::node>::const_iterator it = temp.begin(); it != temp.end();
				it++)
		{
			out << graph.getLabel(*it);
			out << (*it) << ": ";
			list<typename Graph<N, L, W>::node> adj = graph.adjacents((*it));
			for (typename list<typename Graph<N, L, W>::node>::const_iterator it2 = adj.begin(); it2 != adj.end();
					it2++)
				out << graph.getLabel(*it2) << (*it2) << " (" << graph.getWeight((*it), (*it2)) << ") // ";
			out << endl;
		}

	}
	else
		out << "Empty Graph";

	out << endl;

	return out;
}

template<class N, class L, class W>
int Graph<N, L, W>::numNodes() const
{
	return (this->nodesList()).size();
}

template<class N, class L, class W>
int Graph<N, L, W>::numEdges() const
{
	if (this->empty())
		return 0;

	int counter = 0;

	list<node> nodes = this->nodesList();
	list<node> temp = nodes;
	for (typename list<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		for (typename list<node>::iterator it2 = temp.begin(); it2 != temp.end(); it2++)
			if (this->isEdge(*it, *it2))
				counter++;

	return counter;
}

template<class N, class L, class W>
bool Graph<N, L, W>::completeGraph() const
{
	// in a complete direct graph with N nodes the number of edges is N*(N-1)
	int num = this->numNodes();

	return (this->numEdges() == (num * (num - 1)));
}

template<class N, class L, class W>
bool Graph<N, L, W>::connectedGraph() const
{
	list<node> nodes = this->nodesList();
	for (typename list<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		for (typename list<node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++)
			if ((*it != *it2) && !this->isPath(*it, *it2) && !this->isPath(*it2, *it))
				return false;

	return true;

}

template<class N, class L, class W>
bool Graph<N, L, W>::stronglyConnectedGraph() const
{
	list<node> nodes = this->nodesList();
	for (typename list<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		for (typename list<node>::iterator it2 = nodes.begin(); it2 != nodes.end(); it2++)
			if ((*it != *it2) && !this->isPath(*it, *it2))
				return false;

	return true;
}

template<class N, class L, class W>
int Graph<N, L, W>::inGrade(const node curr) const
{
	if (!this->isNode(curr))
		throw std::logic_error("Graph (exception)");

	int counter = 0;
	list<node> temp = this->nodesList();
	for (typename list<node>::iterator it = temp.begin(); it != temp.end(); it++)
		if (this->isEdge((*it), curr))
			counter++;

	return counter;
}

template<class N, class L, class W>
int Graph<N, L, W>::outGrade(const node curr) const
{
	if (!this->isNode(curr))
		throw std::logic_error("Graph (exception)");

	return this->adjacents(curr).size();
}

template<class N, class L, class W>
bool Graph<N, L, W>::linked(const node currNode) const
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph (exception) - Unable to check if linked (node not present)");

	if (this->outGrade(currNode) > 0)
		return true;

	if (this->inGrade(currNode) > 0)
		return true;

	return false;
}

template<class N, class L, class W>
list<typename Graph<N, L, W>::node> Graph<N, L, W>::daisyChained(const node n) const
{
	list<node> nodes = this->adjacents(n);
	int size = (this->numNodes() - 2); // we have already put the adjacent nodes (new max length of the path is size-2)
	int counter = nodes.size(); // number of elements added
	typename list<node>::iterator itStart = nodes.begin();

	for (int i = 0; (i < size && counter != 0); i++) // iterating "size" times we explore all the graph (if we don't add any elements, the search is completed)
	{
		int temp = nodes.size(); // size of the list before adding elements (necessary to know the new starting element)
		int newElementsNumber = counter; // number of new elements added to the list (we'll repeat "newElementsNumber" the following for() )
		counter = 0;

		for (int j = 0; j < newElementsNumber; j++) // it will repeat the for() only for new elements added to the list
		{
			list<node> newNodes = this->adjacents(*itStart);
			for (typename list<node>::iterator it2 = newNodes.begin(); it2 != newNodes.end(); it2++)
				if (std::find(nodes.begin(), nodes.end(), (*it2)) == nodes.end()) // if the node isn't already present in the list
				{
					nodes.push_back(*it2); // add the node
					counter++; // increase the number of elements added
				}

			itStart++; // we'll get the next element in the list
			newNodes.clear();
		}

		// we need to set itStart to the first element added
		itStart = nodes.begin();
		for (int j = 0; j < temp; j++) // temp stores the size of the list before adding new elements
			itStart++;
		// itStart will point to the first new element added
	}

	return nodes;
}

template<class N, class L, class W>
bool Graph<N, L, W>::isLoopNode(const node n) const
{
	list<node> temp = this->daisyChained(n);
	if (std::find(temp.begin(), temp.end(), n) != temp.end())
		return true;

	return false;
}

template<class N, class L, class W>
bool Graph<N, L, W>::acyclicGraph() const
{
	list<node> nodes = this->nodesList();
	int counter = 0;

	for (typename list<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		counter += this->isLoopNode(*it);

	if (counter == 0)
		return true;

	return false;
}

template<class N, class L, class W>
list<typename Graph<N, L, W>::node> Graph<N, L, W>::adjacentsKLevel(const node n, const int k) const
{
	if (k < 0)
		throw std::logic_error("Graph (exception) - Unable to get adjacent nodes (negative distance)");

	if (k == 0) // empty list
	{
		list<node> nodes;
		return nodes;
	}

	list<node> nodes = this->adjacents(n);
	list<node> adjNodesK;
	if (k == 1)
		adjNodesK = nodes;
	int size = (k - 1); // we have already put the adjacent nodes (new max length of the path is size-2)
	int counter = nodes.size(); // number of elements added
	typename list<node>::iterator itStart = nodes.begin();

	for (int i = 0; (i < size && counter != 0); i++) // iterating "size" times we explore all the graph
	{
		int temp = nodes.size(); // size of the list before adding elements (necessary to know the new starting element)
		int newElementsNumber = counter; // number of new elements added to the list (we'll repeat "newElementsNumber" the following for() )
		counter = 0;

		for (int j = 0; j < newElementsNumber; j++) // it will repeat the for() only for new elements added to the list
		{
			list<node> newNodes = this->adjacents(*itStart);
			for (typename list<node>::iterator it2 = newNodes.begin(); it2 != newNodes.end(); it2++)
			{
				if (std::find(nodes.begin(), nodes.end(), (*it2)) == nodes.end()) // if the node isn't already present in the list
				{
					nodes.push_back(*it2); // add the node
					counter++; // increase the number of elements added
				}
				if (i == (k - 2)) // we are on K level
					if (std::find(adjNodesK.begin(), adjNodesK.end(), (*it2)) == adjNodesK.end()) // if the node isn't already present in the list
						adjNodesK.push_back(*it2);
			}

			itStart++; // we'll get the next element in the list
			newNodes.clear();
		}

		// we need to set itStart to the first element added
		itStart = nodes.begin();
		for (int j = 0; j < temp; j++) // temp stores the size of the list before adding new elements
			itStart++;
		// itStart will point to the first new element added
	}

	return adjNodesK;

}

template<class N, class L, class W>
bool Graph<N, L, W>::isPath(const node start, const node end) const
{
	list<node> nodes = this->adjacents(start);

	if (std::find(nodes.begin(), nodes.end(), end) != nodes.end())
		return true;

	int size = (this->numNodes() - 2); // we have already put the adjacent nodes (new max length of the path is size-2)
	int counter = nodes.size(); // number of elements added
	typename list<node>::iterator itStart = nodes.begin();

	for (int i = 0; (i < size && counter != 0); i++) // iterating "size" times we explore all the graph (if we don't add any elements, the search is completed)
	{
		int temp = nodes.size(); // size of the list before adding elements (necessary to know the new starting element)
		int newElementsNumber = counter; // number of new elements added to the list (we'll repeat "newElementsNumber" the following for() )
		counter = 0;

		for (int j = 0; j < newElementsNumber; j++) // it will repeat the for() only for new elements added to the list
		{
			list<node> newNodes = this->adjacents(*itStart);
			for (typename list<node>::iterator it2 = newNodes.begin(); it2 != newNodes.end(); it2++)
			{
				if ((*it2) == end)
					return true;

				if (std::find(nodes.begin(), nodes.end(), (*it2)) == nodes.end()) // if the node isn't already present in the list
				{
					nodes.push_back(*it2); // add the node
					counter++; // increase the number of elements added
				}
			}

			itStart++; // we'll get the next element in the list
			newNodes.clear();
		}

		// we need to set itStart to the first element added
		itStart = nodes.begin();
		for (int j = 0; j < temp; j++) // temp stores the size of the list before adding new elements
			itStart++;
		// itStart will point to the first new element added
	}

	return false;
}

template<class N, class L, class W>
bool Graph<N, L, W>::isNewPath(const node start, const node end, const list<node> holes) const
{
	if (std::find(holes.begin(), holes.end(), end) != holes.end())
		throw std::logic_error("Graph (exception) - Unable to get new path (end node is forbidden)");

	list<node> nodes;
	list<node> adjStart = this->adjacents(start);
	for (typename list<node>::iterator it = adjStart.begin(); it != adjStart.end(); it++) // we can start the algorithm only for valid nodes
		if (std::find(holes.begin(), holes.end(), *it) == holes.end()) // epurate holes
			nodes.push_back(*it);

	if (std::find(nodes.begin(), nodes.end(), end) != nodes.end())
		return true;

	int size = (this->numNodes() - 2); // we have already put the adjacent nodes (new max length of the path is size-2)
	int counter = nodes.size(); // number of elements added
	typename list<node>::iterator itStart = nodes.begin();

	for (int i = 0; (i < size && counter != 0); i++) // iterating "size" times we explore all the graph (if we don't add any elements, the search is completed)
	{
		int temp = nodes.size(); // size of the list before adding elements (necessary to know the new starting element)
		int newElementsNumber = counter; // number of new elements added to the list (we'll repeat "newElementsNumber" the following for() )
		counter = 0;

		for (int j = 0; j < newElementsNumber; j++) // it will repeat the for() only for new elements added to the list
		{
			list<node> newNodes;

			adjStart.clear();
			adjStart = this->adjacents(*itStart);
			for (typename list<node>::iterator it = adjStart.begin(); it != adjStart.end(); it++) // we can continue the algorithm only for valid nodes
				if (std::find(holes.begin(), holes.end(), *it) == holes.end()) // epurate holes
					newNodes.push_back(*it);

			for (typename list<node>::iterator it2 = newNodes.begin(); it2 != newNodes.end(); it2++)
			{
				if ((*it2) == end)
					return true;

				if (std::find(nodes.begin(), nodes.end(), (*it2)) == nodes.end()) // if the node isn't already present in the list
				{
					nodes.push_back(*it2); // add the node
					counter++; // increase the number of elements added
				}
			}

			itStart++; // we'll get the next element in the list
			newNodes.clear();
		}

		// we need to set itStart to the first element added
		itStart = nodes.begin();
		for (int j = 0; j < temp; j++) // temp stores the size of the list before adding new elements
			itStart++;
		// itStart will point to the first new element added
	}

	return false;
}

template<class N, class L, class W>
list<typename Graph<N, L, W>::node> Graph<N, L, W>::getPath(const node start, const node end) const
{
	if (!this->isPath(start, end))
		throw std::logic_error("Graph (exception) - Unable to get path (second node not reachable)");

	int flag = true;
	int stop = false;
	list<node> path;
	list<node> visit;
	path.push_back(start);
	visit.push_back(start);

	while (flag)
	{
		list<node> temp = this->adjacents(path.back()); // check if end is present in the adjacent nodes of the last one added
		if (std::find(temp.begin(), temp.end(), end) != temp.end())
		{
			path.push_back(end);
			flag = false; // search is over: path has been completed
		}
		else
		{
			for (typename list<node>::iterator it = temp.begin(); (it != temp.end() && !stop); it++)
				if (this->isNewPath(*it, end, visit) && std::find(visit.begin(), visit.end(), *it) == visit.end())
				{
					path.push_back(*it);
					visit.push_back(*it);
					stop = true;
				}

			stop = false;
		}
	}

	return path;
}

template<class N, class L, class W>
void Graph<N, L, W>::DFS(const node n) const
{
	if (!this->isNode(n))
		throw std::logic_error("Graph (exception) - Unable to perform DFS (invalid node)");

	list<node> visited;

	cout << n << " ";

	visited.push_back(n);

	list<node> adjNodes = this->adjacents(n);
	for (typename list<node>::iterator it = adjNodes.begin(); it != adjNodes.end(); it++)
		if (std::find(visited.begin(), visited.end(), *it) == visited.end()) // if the node hasn't been visited yet
			DFS(*it, visited);
}

template<class N, class L, class W>
void Graph<N, L, W>::DFS(const node n, list<node>& visited) const
{
	cout << n << " ";

	visited.push_back(n);

	list<node> adjNodes = this->adjacents(n);
	for (typename list<node>::iterator it = adjNodes.begin(); it != adjNodes.end(); it++)
		if (std::find(visited.begin(), visited.end(), *it) == visited.end()) // if the node hasn't been visited yet
			DFS(*it, visited);
}

template<class N, class L, class W>
void Graph<N, L, W>::BFS(const node n) const
{
	queue<node> temp;
	list<node> visited;
	list<node> adjNodes;

	temp.push(n);
	while (!temp.empty())
	{
		node curr = temp.front();
		cout << curr << " ";
		temp.pop();
		visited.push_back(curr);

		adjNodes = this->adjacents(curr);
		for (typename list<node>::iterator it = adjNodes.begin(); it != adjNodes.end(); it++)
			if (std::find(visited.begin(), visited.end(), *it) == visited.end()) // if the node hasn't been visited yet
				temp.push(*it);
		adjNodes.clear();

	}
}

template<class N, class L, class W>
vector<edge<N, W> > Graph<N, L, W>::shortestPath(const node n) const
{
	if (!this->isNode(n))
		throw std::logic_error("Graph (exception) - Unable to calculate shortest path (invalid node)");

	if (!this->connectedGraph())
		throw std::logic_error("Graph (exception) - Unable to calculate shortest path (graph not connected)");

	vector<edge<N, W> > paths;
	list<node> nodes = this->nodesList();
	Set_pointer<node> nodesSet;
	nodesSet.insert(n);
	node temp;

	for (typename list<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if (n != *it)
			paths.push_back(edge<N, W>(n, *it, INT_MAX));
		else
			paths.push_back(edge<N, W>(n, *it, 0));

	while (!nodesSet.empty())
	{
		temp = nodesSet.pickAny();
		nodesSet.erase(temp);
		list<node> adjTemp = this->adjacents(temp);
		for (typename list<node>::iterator it = adjTemp.begin(); it != adjTemp.end(); it++)
			if ((this->pathDistance(temp, paths) + this->getWeight(temp, *it)) < this->pathDistance(*it, paths))
			{
				this->setFatherPath(*it, temp, paths);
				this->setWeightPath(*it, (this->pathDistance(temp, paths) + this->getWeight(temp, *it)), paths);
				if (!nodesSet.find(*it))
					nodesSet.insert(*it);
			}
	}

	return paths;
}

template<class N, class L, class W>
typename Graph<N, L, W>::weight Graph<N, L, W>::pathDistance(const node n, const vector<edge<N, W> > paths) const
{
	weight currWeight;
	for (typename vector<edge<N, W> >::const_iterator it = paths.begin(); it != paths.end(); it++)
		if ((*it).endNode == n)
			currWeight = (*it).weight;

	return currWeight;
}

template<class N, class L, class W>
void Graph<N, L, W>::setFatherPath(const node son, const node father, vector<edge<N, W> >& paths) const
{
	for (typename vector<edge<N, W> >::iterator it = paths.begin(); it != paths.end(); it++)
		if ((*it).endNode == son)
			(*it).startNode = father;
}

template<class N, class L, class W>
void Graph<N, L, W>::setWeightPath(const node n, const weight newWeight, vector<edge<N, W> >& paths) const
{
	for (typename vector<edge<N, W> >::iterator it = paths.begin(); it != paths.end(); it++)
		if ((*it).endNode == n)
			(*it).weight = newWeight;
}

template<class N, class L, class W>
list<typename Graph<N, L, W>::node> Graph<N, L, W>::getShortestPath(const node start, const node end) const
{
	if (!this->isNode(start) || !this->isNode(end))
		throw std::logic_error("Graph (exception) - Unable to calculate shortest path (invalid node)");

	if (!this->isPath(start, end))
		throw std::logic_error("Graph (exception) - Unable to calculate shortest path (path not present)");

	vector<edge<N, W> > minPaths = this->shortestPath(start);
	list<node> bestPath;
	bestPath.push_front(end);

	typename vector<edge<N, W> >::iterator it = minPaths.begin();
	node tempNode;

	while ((*it).endNode != end)
		it++;

	while ((*it).startNode != start)
	{
		bestPath.push_front((*it).startNode);
		tempNode = (*it).startNode;
		it = minPaths.begin();
		while ((*it).endNode != tempNode)
			it++;
	}

	bestPath.push_front(start);

	return bestPath;
}

template<class N, class L, class W>
list<edge<N, W> > Graph<N, L, W>::edgesList() const
{
	list<edge<N, W> > edgesList;

	list<node> list1 = this->nodesList();
	list<node> list2 = list1;

	for (typename list<node>::iterator it = list1.begin(); it != list1.end(); it++)
		for (typename list<node>::iterator it2 = list2.begin(); it2 != list2.end(); it2++)
			if (this->isEdge(*it, *it2))
				edgesList.push_back(edge<N, W>(*it, *it2, this->getWeight(*it, *it2)));

	return edgesList;
}

template<class N, class L, class W>
void Graph<N, L, W>::clearEdges()
{
	list<node> list1 = this->nodesList();
	list<node> list2 = list1;

	for (typename list<node>::iterator it = list1.begin(); it != list1.end(); it++)
		for (typename list<node>::iterator it2 = list2.begin(); it2 != list2.end(); it2++)
			if (this->isEdge(*it, *it2))
				this->eraseEdge(*it, *it2);
}

template<class N, class L, class W>
Set_pointer<edge<N,W> > Graph<N, L, W>::MST()
{
	if (!this->connectedGraph())
		throw std::logic_error("Graph (exception) - Unable to calculate MST (not connected graph)");

	Set_pointer<edge<node, weight> > edges; // set of edges of the MST
	Set_pointer<node> nodes; // set with all the nodes of the graph
	list<node> nodesList = this->nodesList();

	while (!nodesList.empty()) // convert the list of nodes in a set of nodes
	{
		nodes.insert(nodesList.front());
		nodesList.pop_front();
	}

	MFSet_set<node> mfset(nodes); // create the MFSet with the set that has just been built

	list<edge<N, W> > edgesList = this->edgesList();
	edgesList.sort(); // sort the list of edges

	for (typename list<edge<N, W> >::iterator it = edgesList.begin(); it != edgesList.end(); it++) // for each edge
		if (mfset.find((*it).startNode) != mfset.find((*it).endNode)) // if nodes belong to different components
		{
			mfset.merge((*it).startNode, (*it).endNode);
			edges.insert(*it);
			edges.insert(edge<N, W>((*it).endNode, (*it).startNode, (*it).weight)); // insert the edge also in the opposite direction
		}

	return edges;
}

template<class N, class L, class W>
void Graph<N, L, W>::convertToMST()
{
	Set_pointer<edge<N,W> > edges = this->MST();

	this->clearEdges(); // remove edges of the graph

	while (!edges.empty()) // reinsert only the strictly necessary edges
	{
		edge<node, weight> temp = edges.pickAny();
		edges.erase(temp);
		this->insEdge(temp.startNode, temp.endNode);
		this->setWeight(temp.startNode, temp.endNode, temp.weight);
	}
}

#endif /* _GRAPH_H_ */
