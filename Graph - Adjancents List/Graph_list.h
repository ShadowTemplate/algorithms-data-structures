#ifndef _GRAPHADJLIST_H
#define _GRAPHADJLIST_H

#include "Graph.h"
#include "Node.h"
#include "Row.h"

template<class V, class W>
class Graph_list: public Graph<Node, V, W>
{
public:
	typedef typename Graph<Node, V, W>::node node;
	typedef typename Graph<Node, V, W>::label label;
	typedef typename Graph<Node, V, W>::weight weight;

	Graph_list();
	Graph_list(const Graph_list<V, W>&);
	~Graph_list();

	Graph_list<V, W>& operator =(const Graph_list<V, W>&);

	void create();
	bool empty() const;
	void insNode(node&);
	void insEdge(const node, const node);
	bool isNode(const node) const;
	bool isEdge(const node, const node) const;
	void eraseNode(const node);
	void eraseEdge(const node, const node);
	list<node> adjacents(const node) const;
	list<node> nodesList() const;
	label getLabel(const node) const;
	void setLabel(const node, const label);
	weight getWeight(const node, const node) const;
	void setWeight(const node, const node, const weight);

private:
	list<Row<V, W> > matrix;
	int currID;

	typename list<Row<V, W> >::const_iterator getRow(const node) const;
	typename list<Row<V, W> >::iterator getRow(const node);

};

template<class V, class W>
Graph_list<V, W>::Graph_list()
{
	currID = 0;
	this->create();
}

template<class V, class W>
Graph_list<V, W>::Graph_list(const Graph_list<V, W>& g2)
{
	*this = g2;
}

template<class V, class W>
Graph_list<V, W>::~Graph_list()
{
	while (!this->matrix.empty())
		this->matrix.pop_back();

	this->currID = 0;
}

template<class V, class W>
Graph_list<V, W>& Graph_list<V, W>::operator =(const Graph_list<V, W>& g2)
{
	if (&g2 != this) // avoid auto-assignment
	{
		while (!this->matrix.empty())
			this->matrix.pop_back();

		this->matrix = g2.matrix;
		this->currID = g2.currID;
	}
	return *this;
}

template<class V, class W>
void Graph_list<V, W>::create()
{
	currID = 0;
}

template<class V, class W>
bool Graph_list<V, W>::empty() const
{
	return (currID == 0);
}

template<class V, class W>
void Graph_list<V, W>::insNode(node& newNode)
{
	if (newNode.getID() != -1) // the node belongs to a graph
		throw std::logic_error("Graph_list (exception) - Unable to insert node (already used)");

	newNode.setID(this->currID);
	currID++;

	matrix.push_back(Row<V, W>(newNode.getID()));
}

template<class V, class W>
void Graph_list<V, W>::insEdge(const node start, const node end)
{
	if (!this->isNode(start) || !this->isNode(end))
		throw std::logic_error("Graph_list (exception) - Unable to insert edge (node not present)");

	if (this->isEdge(start, end))
		throw std::logic_error("Graph_list (exception) - Unable to insert edge (edge already present)");

	(*this->getRow(start)).adjacents.push_back(edgeRow<W>(start.getID(), end.getID()));
}

template<class V, class W>
bool Graph_list<V, W>::isNode(const node currNode) const
{
	if (this->empty())
		return false;

	for (typename list<Row<V, W> >::const_iterator it = this->matrix.begin(); it != this->matrix.end(); it++)
		if ((*it).nodeID == currNode.getID())
			return true;

	return false;
}

template<class V, class W>
bool Graph_list<V, W>::isEdge(const node start, const node end) const
{
	if (!this->isNode(start) || !this->isNode(end))
		throw std::logic_error("Graph_list (exception) - Unable to check edge (node not present)");

	Row<V, W> currRow = *(this->getRow(start));

	for (typename list<edgeRow<W> >::iterator it = currRow.adjacents.begin(); it != currRow.adjacents.end(); it++)
		if ((*it).destID == end.getID())
			return true;

	return false;
}

template<class V, class W>
void Graph_list<V, W>::eraseNode(const node currNode)
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to erase node (node not present)");

	if (this->linked(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to erase node (node linked to others)");

	matrix.erase(this->getRow(currNode));
}

template<class V, class W>
void Graph_list<V, W>::eraseEdge(const node node1, const node node2)
{
	if (!this->isNode(node1) || !this->isNode(node2))
		throw std::logic_error("Graph_list (exception) - Unable to erase edge (node not present)");

	if (!this->isEdge(node1, node2))
		throw std::logic_error("Graph_list (exception) - Unable to erase edge (edge not present)");

	bool flag = true;

	for (typename list<edgeRow<W> >::iterator it = (*this->getRow(node1)).adjacents.begin();
			(it != (*this->getRow(node1)).adjacents.end() && flag); it++)
		if ((*it).destID == node2.getID())
		{
			(*this->getRow(node1)).adjacents.erase(it);
			flag = false;
		}
}

template<class V, class W>
list<typename Graph_list<V, W>::node> Graph_list<V, W>::adjacents(const node currNode) const
{
	list<node> nodes;

	Row<V, W> currRow = *(this->getRow(currNode));

	for (typename list<edgeRow<W> >::iterator it = currRow.adjacents.begin(); it != currRow.adjacents.end(); it++)
	{
		node temp;
		temp.setID((*it).destID);
		nodes.push_back(temp);
	}

	return nodes;
}

template<class V, class W>
list<typename Graph_list<V, W>::node> Graph_list<V, W>::nodesList() const
{
	list<node> nodes;

	for (typename list<Row<V, W> >::const_iterator it = this->matrix.begin(); it != this->matrix.end(); it++)
	{
		node temp;
		temp.setID((*it).nodeID);
		nodes.push_back(temp);
	}

	return nodes;
}

template<class V, class W>
typename Graph_list<V, W>::label Graph_list<V, W>::getLabel(const node currNode) const
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to get label (node not present)");

	return (*(this->getRow(currNode))).nodeValue;
}

template<class V, class W>
void Graph_list<V, W>::setLabel(const node currNode, const label newLabel)
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to set label (node not present)");

	(*(this->getRow(currNode))).nodeValue = newLabel;
}

template<class V, class W>
typename Graph_list<V, W>::weight Graph_list<V, W>::getWeight(const node start, const node end) const
{
	if (!this->isNode(start) || !this->isNode(end))
		throw std::logic_error("Graph_list (exception) - Unable to get weight (node not present)");

	if (!this->isEdge(start, end))
		throw std::logic_error("Graph_list (exception) - Unable to get weight (edge not present)");

	Row<V, W> currRow = *(this->getRow(start));

	for (typename list<edgeRow<W> >::iterator it = currRow.adjacents.begin(); it != currRow.adjacents.end();
			it++)
		if ((*it).destID == end.getID())
			return (*it).weight;

	throw std::logic_error("Graph_list (exception) - Unable to get weight");
}

template<class V, class W>
void Graph_list<V, W>::setWeight(node start, node end, const weight newWeight)
{
	if (!this->isNode(start) || !this->isNode(end))
		throw std::logic_error("Graph_list (exception) - Unable to set weight (node not present)");

	if (!this->isEdge(start, end))
		throw std::logic_error("Graph_list (exception) - Unable to set weight (edge not present)");

	bool flag = true;

	for (typename list<edgeRow<W> >::iterator it = (*this->getRow(start)).adjacents.begin();
			(it != (*this->getRow(start)).adjacents.end() && flag); it++)
		if ((*it).destID == end.getID())
		{
			(*it).weight = newWeight;
			flag = false;
		}
}

template<class V, class W>
typename list<Row<V, W> >::const_iterator Graph_list<V, W>::getRow(const node currNode) const
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to get row of the node (invalid node)");

	typename list<Row<V, W> >::const_iterator it = this->matrix.begin();

	while ((*it).nodeID != currNode.getID())
		it++;

	return it;
}

template<class V, class W>
typename list<Row<V, W> >::iterator Graph_list<V, W>::getRow(const node currNode)
{
	if (!this->isNode(currNode))
		throw std::logic_error("Graph_list (exception) - Unable to get row of the node (invalid node)");

	typename list<Row<V, W> >::iterator it = this->matrix.begin();

	while ((*it).nodeID != currNode.getID())
		it++;

	return it;
}

#endif // _GRAPHADJLIST_H
