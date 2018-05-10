#ifndef _BINTREEC_H
#define _BINTREEC_H

#include "Bin_tree.h"

template<class T>
class BinTree_cursor: public BinTree<T, int>
{
	static const int NIL = -1;

public:

	typedef typename BinTree<T, int>::value_type value_type;
	typedef typename BinTree<T, int>::node node;

	typedef struct _cella
	{
		node father;
		node left;
		node right;
		value_type value;
	} Cell;

	BinTree_cursor();
	BinTree_cursor(int); // size
	BinTree_cursor(const BinTree_cursor<T>&);
	~BinTree_cursor();

	BinTree_cursor<T>& operator =(const BinTree_cursor<T>&);

	void create(); // create the binary tree
	bool empty() const; // true if the tree is empty
	node root() const; // return the root node
	node parent(node) const; // return the father of the node
	node left(node) const; // return the left son
	node right(node) const; // return the right son
	bool left_empty(node) const; // true if there isn't a left son
	bool right_empty(node) const; // true if there isn't a right son
	void erase(node); // erase the subtree having root = node
	value_type read(node) const; // read the element in the node
	void write(node, value_type); // write the element in the node
	void ins_root(node); // insert the root
	void ins_left(node); // insert an empty node in the left son
	void ins_right(node); // insert an empty node in the right son

private:
	int MAXLENGTH;
	Cell* space;
	int nodesNum;
	node start;
	node freeCell;

	void arrayDoubling(Cell*&, const int, const int);
};

template<class T>
BinTree_cursor<T>::BinTree_cursor()
{
	MAXLENGTH = 100;
	space = new Cell[MAXLENGTH];
	nodesNum = 0;
	this->create();
}

template<class T>
BinTree_cursor<T>::BinTree_cursor(int size)
{
	if (size <= 0)
		throw std::logic_error("BinTree_cursor (exception) - Unable to initialise (non-positive size)");

	MAXLENGTH = size;
	space = new Cell[size];
	nodesNum = 0;
	this->create();
}

template<class T>
BinTree_cursor<T>::BinTree_cursor(const BinTree_cursor<T>& tree)
{
	nodesNum = 0;
	*this = tree;
}

template<class T>
BinTree_cursor<T>::~BinTree_cursor()
{
	if (!this->empty())
		this->erase(this->root());

	delete[] space;
	MAXLENGTH = 0;
	nodesNum = 0;
	start = 0;
	freeCell = 0;
}

template<class T>
BinTree_cursor<T>& BinTree_cursor<T>::operator =(const BinTree_cursor<T>& tree)
{
	if (&tree != this) // avoid auto-assignment
	{
		if (!this->empty())
		{
			this->erase(this->root());
			delete[] space;
		}

		MAXLENGTH = tree.MAXLENGTH;
		nodesNum = tree.nodesNum;
		start = tree.start;
		freeCell = tree.freeCell;
		space = new Cell[MAXLENGTH];

		for (int i = 0; i < MAXLENGTH; i++)
			space[i] = tree.space[i];
	}

	return *this;
}

template<class T>
void BinTree_cursor<T>::create()
{
	start = NIL;

	for (int i = 0; i < MAXLENGTH; i++)
	{
		space[i].left = (i + 1) % MAXLENGTH; // we save in "left" field an index of the next (free) position in space[]
		space[i].value = value_type();
	}

	freeCell = 0;
	nodesNum = 0;
}

template<class T>
bool BinTree_cursor<T>::empty() const
{
	return (nodesNum == 0);
}

template<class T>
typename BinTree_cursor<T>::node BinTree_cursor<T>::root() const
{
	if (this->empty())
		throw std::logic_error("BinTree_cursor (exception) - Unable to read root (empty tree)");

	return start;
}

template<class T>
typename BinTree_cursor<T>::node BinTree_cursor<T>::parent(node n) const
{
	if (n != start)
		return space[n].father;
	else
		return n;
}

template<class T>
typename BinTree_cursor<T>::node BinTree_cursor<T>::left(node n) const
{
	if (!this->left_empty(n))
		return (space[n].left);
	else
		return n;
}

template<class T>
typename BinTree_cursor<T>::node BinTree_cursor<T>::right(node n) const
{
	if (!this->right_empty(n))
		return (space[n].right);
	else
		return n;
}

template<class T>
bool BinTree_cursor<T>::left_empty(node n) const
{
	return (space[n].left == NIL);
}

template<class T>
bool BinTree_cursor<T>::right_empty(node n) const
{
	return (space[n].right == NIL);
}

template<class T>
void BinTree_cursor<T>::erase(node n)
{
	if (n != NIL)
	{
		if (!this->left_empty(n))
			this->erase(space[n].left);
		if (!this->right_empty(n))
			this->erase(space[n].right);
		if (n != start)
		{
			node p = this->parent(n);
			if (space[p].left == n)
				space[p].left = NIL;
			else
				space[p].right = NIL;
		}
		else
			start = NIL;
		nodesNum--;
		space[n].left = freeCell;
		freeCell = n;
	}
	else
		throw std::logic_error("BinTree_cursor (exception) - Unable to erase (null node)");
}

template<class T>
typename BinTree_cursor<T>::value_type BinTree_cursor<T>::read(node n) const
{
	return space[n].value;
}

template<class T>
void BinTree_cursor<T>::write(node n, value_type a)
{
	space[n].value = a;
}

template<class T>
void BinTree_cursor<T>::ins_root(node n)
{
	if (start != NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert root (already exists)");

	start = freeCell; // free = 0
	freeCell = space[freeCell].left; // set the next free space
	space[start].left = NIL; // set left son
	space[start].right = NIL; // set right son
	space[start].father = NIL; // set father
	nodesNum++;

	if (n != 0)
	{
		try
		{
			this->write(this->root(), this->read(n));
		} catch (std::logic_error&)
		{
		};
	}
}

template<class T>
void BinTree_cursor<T>::ins_left(node n)
{
	if (start == NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (empty tree)");
	if (n == NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (null node)");
	if (space[n].left != NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (already exists)");

	if (nodesNum >= MAXLENGTH)
		this->arrayDoubling(space, MAXLENGTH, MAXLENGTH*2);

	node q = freeCell; // q = position of the son
	freeCell = space[freeCell].left; // set the next free space
	space[n].left = q; // set the left son
	space[q].father = n;
	space[q].left = NIL; // set an empty son
	space[q].right = NIL; // set an empty son
	nodesNum++;
}

template<class T>
void BinTree_cursor<T>::ins_right(node n)
{
	if (start == NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (empty tree)");
	if (n == NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (null node)");
	if (space[n].right != NIL)
		throw std::logic_error("BinTree_cursor (exception) - Unable to insert node (already exists)");

	if (nodesNum >= MAXLENGTH)
		this->arrayDoubling(space, MAXLENGTH, MAXLENGTH*2);

	node q = freeCell; // position of the son
	freeCell = space[freeCell].left; // set the next free space
	space[n].right = q; // set the right son
	space[q].father = n;
	space[q].left = NIL; // set an empty son
	space[q].right = NIL; // set an empty son
	nodesNum++;
}

template<class T>
void BinTree_cursor<T>::arrayDoubling(Cell*& a, const int vecchiaDim, const int nuovaDim)
{
	Cell* temp = new Cell[nuovaDim];

	int number;
	if (vecchiaDim < nuovaDim)
		number = vecchiaDim;
	else
		number = nuovaDim;

	freeCell = MAXLENGTH;
	MAXLENGTH = nuovaDim;

	for (int i = 0; i < nuovaDim; i++)
	{
		temp[i].left = (i + 1) % nuovaDim;
		temp[i].value = value_type();
	}

	for (int i = 0; i < number; i++)
		temp[i] = a[i];

	delete[] a;
	a = temp;
}

#endif // _BINTREEC_H
