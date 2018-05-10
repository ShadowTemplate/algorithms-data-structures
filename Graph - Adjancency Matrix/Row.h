#ifndef _ROW_H
#define _ROW_H

#include <vector>
using std::vector;

const unsigned MAXNODES = 100;

template<class W>
class edgeRow
{
public:
	int startID;
	int destID;
	W weight;
	bool flag;

	edgeRow()
	{
		startID = -1;
		destID = -1;
		weight = W();
		flag = false;
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
			this->flag = newEdge.flag;
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
	bool flag;
	vector<edgeRow<W> > adjacents;

	Row(const int newID)
	{
		nodeID = newID;
		nodeValue = V();
		flag = false;
		adjacents.resize(MAXNODES);
		int counter = 0;
		for(typename vector<edgeRow<W> >::iterator it = adjacents.begin(); it != adjacents.end(); it++)
		{
			(*it).startID = newID;
			(*it).destID = counter;
			counter++;
		}
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
			this->flag = row2.flag;
			this->adjacents = row2.adjacents;
		}
		return *this;
	}
};

#endif // _ROW_H
