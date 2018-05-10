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
		startNode = node(); //-1
		endNode = node(); //-1
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

	bool operator ==(const edge<N, W>& e2) const
	{
		if (this->startNode != e2.startNode)
			return false;

		if (this->endNode != e2.endNode)
			return false;

		if (this->weight != e2.weight)
			return false;

		return true;
	}

	bool operator !=(const edge<N, W>& e2) const
	{
		return (!(*this == e2));
	}

	bool operator <(const edge<N, W>& e2) const
	{
		if (this->weight < e2.weight)
			return true;

		return false;
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
