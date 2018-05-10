#ifndef _EDGE_H
#define _EDGE_H

#include <iostream>
using std::ostream;

template<class N, class W>
class edge
{
public:
	typedef N node;

	node startNode;
	node endNode;
	W weight;

	edge()
	{
		startNode = -1;
		endNode = -1;
		weight = W();
	}

	edge(const node start, const node end, const W newWeight)
	{
		startNode = start;
		endNode = end;
		weight = newWeight;
	}

	edge(const edge<N, W>& newEdge)
	{
		*this = newEdge;
	}
	edge<N, W>& operator =(const edge<N, W>& newEdge)
	{
		if (&newEdge != this) // avoid auto-assignment
		{
			this->startNode = newEdge.startNode;
			this->endNode = newEdge.endNode;
			this->weight = newEdge.weight;
		}
		return *this;
	}
	~edge()
	{
	}
};

template<class N, class W>
ostream& operator <<(ostream& out, const edge<N, W>& edge)
{
	out << edge.startNode;
	out << " -> ";
	out << edge.endNode;
	out << ": ";
	out << edge.weight;
	out << std::endl;

	return out;

}

#endif // _EDGE_H
