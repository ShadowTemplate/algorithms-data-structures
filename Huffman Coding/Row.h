#ifndef _ROW_H
#define _ROW_H

#include <list>
using std::list;

template<class W>
class edgeRow
{
public:
	int startID;
	int destID;
	W weight;

	edgeRow(const int start, const int end)
	{
		startID = start;
		destID = end;
		weight = W();
	}

	edgeRow(const edgeRow<W>& newEdge)
	{
		*this = newEdge;
	}
	edgeRow<W>& operator =(const edgeRow<W>& newEdge)
	{
		if (&newEdge != this) // avoid auto-assignment
		{
			this->startID = newEdge.startID;
			this->destID = newEdge.destID;
			this->weight = newEdge.weight;
		}
		return *this;
	}
	~edgeRow()
	{
	}
};

template<class V, class W>
class Row
{
public:

	int nodeID;
	V nodeValue;
	list<edgeRow<W> > adjacents;

	Row(const int newID)
	{
		nodeID = newID;
		nodeValue = V();
	}

	Row(const Row<V, W>& row2)
	{
		*this = row2;
	}

	~Row()
	{
		while(!adjacents.empty())
			adjacents.pop_back();
	}

	Row<V, W>& operator =(const Row<V, W>& row2)
	{
		if (&row2 != this) // avoid auto-assignment
		{
			this->nodeID = row2.nodeID;
			this->nodeValue = row2.nodeValue;
			this->adjacents = row2.adjacents;
		}
		return *this;
	}
};

#endif // _ROW_H
