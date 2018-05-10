#ifndef _NARYTREECHILDLIST_H
#define _NARYTREECHILDLIST_H

const int defaultNumber = 15;

#include "listap.h"
#include "N-aryTree.h"

template<class T>
class NaryTree_childList: public NaryTree<T, int>
{
public:

	typedef typename NaryTree<T, int>::value_type value_type;
	typedef typename NaryTree<T, int>::node node;
	typedef List_pointer<int>::position position;

	struct Record
	{
		value_type value;
		bool used;
		List_pointer<int> children;
	};

	NaryTree_childList();
	NaryTree_childList(const value_type&);
	NaryTree_childList(const NaryTree_childList<T>&);
	~NaryTree_childList();

	NaryTree_childList<T>& operator =(const NaryTree_childList<T>&);

	void create(); // create the binary tree
	bool empty() const; // true if the three is empty
	void ins_root(node); // insert the root
	node root() const; // return the root node
	node parent(const node&) const; // return the father of the node
	bool is_leaf(const node&) const; // true if the node is a leaf
	node firstChild(const node&) const; // return the first child of the node
	bool lastSibling(const node&) const; // true if the node doesn't have a right sibling
	node nextSibling(const node&) const; // return the right sibling of the node
	void insFirstSubTree(node, const NaryTree<value_type, node>&); // add the tree like the first child of the node
	void insSubTree(node, const NaryTree<value_type, node>&); // add the tree like sibling of the node
	void erase(node); // erase the subtree having root = node
	value_type read(const node&) const; // read the element in the node
	void write(node, const value_type&); // write the element in the node

	node lastChild(const node) const; // return the last child of the node
	bool firstSibling(const node) const; // true if the node is the first child
	node prevSibling(const node) const; // return the left sibling of the node
	void insFirstChild(node); // add a child to the node (leftmost)
	void insLastChild(node); // add a child to the node (rightmost)
	void insRightSibling(node); // add a right sibling to the node
	void build(NaryTree_childList<T>, NaryTree_childList<T>); // build a new tree: implicit tree must be empty, other two !empty
	void erase(); // erase the all tree
	void copyGeneralTree(node, const NaryTree<value_type, node>&, node); // copy a tree in the implicit subtree, starting from the nodes

private:
	Record* nodes;
	node tree_root;
	int numNodes;
	int MAXNODES;

	void arrayDoubling(Record*&, const int, const int);
};

template<class T>
NaryTree_childList<T>::NaryTree_childList()
{
	nodes = 0;
	tree_root = 0;
	numNodes = 0;
	MAXNODES = defaultNumber;
	this->create();
}

template<class T>
NaryTree_childList<T>::NaryTree_childList(const value_type& value)
{
	nodes = 0;
	numNodes = 0;
	tree_root = 0;
	MAXNODES = defaultNumber;
	this->create();

	node new_root = 0;
	this->ins_root(new_root);
	this->write(this->root(), value);
}

template<class T>
NaryTree_childList<T>::NaryTree_childList(const NaryTree_childList<T>& tree)
{
	nodes = 0;
	numNodes = 0;
	tree_root = 0;
	MAXNODES = defaultNumber;
	*this = tree;
}

template<class T>
NaryTree_childList<T>::~NaryTree_childList()
{
	delete[] nodes;
}

template<class T>
NaryTree_childList<T>& NaryTree_childList<T>::operator =(const NaryTree_childList<T>& tree)
{
	if (&tree != this) // avoid auto-assignment
	{
		if (!this->empty())
			this->erase();

		this->MAXNODES = tree.MAXNODES;
		this->create();

		if (!tree.empty())
		{
			node newroot = 0;
			this->ins_root(newroot);
			this->copyGeneralTree(this->root(), tree, tree.root());
		}
	}
	return *this;
}

template<class T>
void NaryTree_childList<T>::create()
{
	numNodes = 0;
	tree_root = 0;

	nodes = new Record[MAXNODES];

	for (int i = 0; i < MAXNODES; i++)
	{
		nodes[i].value = value_type();
		nodes[i].used = false;
		nodes[i].children.create();
	}
}

template<class T>
bool NaryTree_childList<T>::empty() const
{
	return (numNodes == 0);
}

template<class T>
void NaryTree_childList<T>::ins_root(node n)
{
	if (!this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert root (already present)");

	tree_root = 0;
	nodes[0].used = true;
	numNodes++;

	if (n != 0)
		this->write(this->root(), this->read(n));
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::root() const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve root (already present)");

	return tree_root;
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::parent(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve parent (empty tree)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to get parent (root)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve parent (invalid node)");

	position child;
	int p;
	for (int i = 0; i < MAXNODES; i++)
	{
		if (!nodes[i].children.empty())
		{
			child = nodes[i].children.begin();
			bool found = false;
			while (!nodes[i].children.end(child) && !found)
			{
				if (nodes[i].children.read(child) == n)
				{
					found = true;
					p = i;
				}
				child = nodes[i].children.next(child);
			}
			if (found)
				return (i);
		}
	}

	throw std::logic_error("NaryTree_listChild (exception) - Unable to get parent (root)");
}

template<class T>
bool NaryTree_childList<T>::is_leaf(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check if node is leaf (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check if node is leaf (invalid node)");

	return (nodes[n].children.empty());
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::firstChild(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve first child (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve first child (invalid node)");

	if (this->is_leaf(n))
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve firstChild (node is leaf)");

	return nodes[n].children.read(nodes[n].children.begin());
}

template<class T>
bool NaryTree_childList<T>::lastSibling(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check if node is last sibling (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check if node is last sibling (invalid node)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check node (root doesn't have sibling)");

	node p = this->parent(n);
	position c = nodes[p].children.begin();

	while (!nodes[p].children.end(nodes[p].children.next(c)))
		c = nodes[p].children.next(c);

	return (n == nodes[p].children.read(c));
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::nextSibling(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check node (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve next sibling (invalid node)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check node (root doesn't have sibling)");

	if (this->lastSibling(n))
		throw std::logic_error("NaryTree_listChild (exception) - Unable to get next sibling (node is last sibling)");

	node p = this->parent(n);
	position c = nodes[p].children.begin();
	while (!nodes[p].children.end(c))
	{
		if (nodes[p].children.read(c) == n)
			return nodes[p].children.read(nodes[p].children.next(c));
		c = nodes[p].children.next(c);
	}

	throw std::logic_error("NaryTree_listChild (exception) - Unable to get next sibling");
}

template<class T>
void NaryTree_childList<T>::insFirstSubTree(node n1, const NaryTree<value_type, node>& t)
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (empty tree)");

	if (nodes[n1].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (invalid node)");

	if (t.empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (empty subtree)");

	if (!this->is_leaf(n1))
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (node is not a leaf)");

	this->insFirstChild(n1);
	node temp = this->firstChild(n1);

	this->copyGeneralTree(temp, t, t.root());
}

template<class T>
void NaryTree_childList<T>::insSubTree(node n, const NaryTree<value_type, node>& t2)
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (invalid node)");

	if (t2.empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (empty subtree)");

	if (n == this->root())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert subtree (node is root)");

	this->insRightSibling(n);
	node temp = this->nextSibling(n);
	node root = t2.root();
	this->copyGeneralTree(temp, t2, root);
}

template<class T>
void NaryTree_childList<T>::erase(node n)
{
	if (this->empty())
		throw std::logic_error("NaryTree_listChild (exception) - Unable to erase node (empty tree)");

	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to erase node (invalid node)");

	if (!this->is_leaf(n))
		while (!nodes[n].children.empty())
			this->erase(nodes[n].children.read(nodes[n].children.begin()));

	if (n != 0)
	{
		node p = parent(n);
		position c = nodes[p].children.begin();
		while (nodes[p].children.read(c) != n)
			c = nodes[p].children.next(c);
		nodes[p].children.erase(c);
	}
	nodes[n].value = value_type();
	nodes[n].used = false;
	numNodes--;
}

template<class T>
typename NaryTree_childList<T>::value_type NaryTree_childList<T>::read(const node& n) const
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to read label (invalid node)");

	return (nodes[n].value);
}

template<class T>
void NaryTree_childList<T>::write(node n, const value_type& el)
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to write label (invalid node)");

	nodes[n].value = el;
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::lastChild(const node n) const
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve last child (invalid node)");

	if (this->is_leaf(n))
		throw std::logic_error("NaryTree_listChild (exception) - Unable to read child (node is leaf)");

	position c = nodes[n].children.begin();
	while (!nodes[n].children.end(nodes[n].children.next(c)))
		c = nodes[n].children.next(c);

	return nodes[n].children.read(c);
}

template<class T>
bool NaryTree_childList<T>::firstSibling(const node n) const
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to check if node is first sibling (invalid node)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to get sibling (root doesn't have)");

	return n == this->firstChild(this->parent(n));
}

template<class T>
typename NaryTree_childList<T>::node NaryTree_childList<T>::prevSibling(const node n) const
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to retrieve previous sibling (invalid node)");

	if (this->firstSibling(n))
		throw std::logic_error("NaryTree_listChild (exception) - Unable to get previous sibling (first child)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to get sibling (root doesn't have)");

	node previous = this->firstChild(this->parent(n));

	while (this->nextSibling(previous) != n)
		previous = this->nextSibling(previous);

	return previous;
}

template<class T>
void NaryTree_childList<T>::insFirstChild(node n)
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert child (invalid node)");

	if (numNodes >= MAXNODES)
		this->arrayDoubling(nodes, MAXNODES, MAXNODES * 2);

	int k = 0;
	while (k < MAXNODES && nodes[k].used == true) // find a free position in nodes[]
		k++;

	nodes[k].used = true;
	nodes[n].children.insert(k, nodes[n].children.begin());
	numNodes++;

}

template<class T>
void NaryTree_childList<T>::insLastChild(node n)
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert child (invalid node)");

	if (numNodes >= MAXNODES)
		this->arrayDoubling(nodes, MAXNODES, MAXNODES * 2);

	if (!nodes[n].children.empty())
	{
		node temp = this->lastChild(n);
		this->insRightSibling(temp);
	}
	else
		this->insFirstChild(n);
}

template<class T>
void NaryTree_childList<T>::insRightSibling(node n)
{
	if (nodes[n].used == false)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert child (invalid node)");

	if (n == tree_root)
		throw std::logic_error("NaryTree_listChild (exception) - Unable to insert sibling (root can't have)");

	if (numNodes >= MAXNODES)
		this->arrayDoubling(nodes, MAXNODES, MAXNODES * 2);

	int k = 0;
	while (k < MAXNODES && nodes[k].used == true) // find a free position in nodes[]
		k++;

	nodes[k].used = true;
	node p = this->parent(n);
	position child = nodes[p].children.begin();
	bool found = false;
	while (!nodes[p].children.end(child) && !found)
	{
		if (nodes[p].children.read(child) == n)
			found = true;
		child = nodes[p].children.next(child);
	}
	nodes[p].children.insert(k, child);
	numNodes++;

}

template<class T>
void NaryTree_childList<T>::build(NaryTree_childList<T> t1, NaryTree_childList<T> t2)
{
	if (!this->empty() || t1.empty() || t2.empty())
		throw std::logic_error("NaryTree_childList (exception) - Unable to build tree");

	node temp = 0;
	this->ins_root(temp);
	this->write(this->root(), value_type());
	temp = this->root();
	this->insFirstSubTree(temp, t1);
	temp = this->firstChild(root());
	this->insSubTree(temp, t2);
}

template<class T>
void NaryTree_childList<T>::erase()
{
	this->erase(this->root());
}

template<class T>
void NaryTree_childList<T>::copyGeneralTree(node n1, const NaryTree<value_type, node>&t2, node n2)
{
	this->write(n1, t2.read(n2));

	if (!t2.is_leaf(n2))
	{
		node temp;
		node temp2;

		for (temp = t2.firstChild(n2); !t2.lastSibling(temp); temp = t2.nextSibling(temp))
		{
			// we are not on the first child of n2
			if (t2.firstChild(n2) != temp)
			{
				node t = this->lastChild(n1);
				this->insRightSibling(t);
				temp2 = this->lastChild(n1);
			}
			else
			{
				this->insFirstChild(n1);
				temp2 = this->firstChild(n1);
			}

			this->copyGeneralTree(temp2, t2, temp);
		}

		// we are not on the first child of n2
		if (t2.firstChild(n2) != temp)
		{
			this->insRightSibling(this->lastChild(n1));
			temp2 = this->lastChild(n1);
		}
		else
		{
			this->insFirstChild(n1);
			temp2 = this->firstChild(n1);
		}
		this->copyGeneralTree(temp2, t2, temp);
	}
}

template<class T>
void NaryTree_childList<T>::arrayDoubling(Record*& a, const int vecchiaDim, const int nuovaDim)
{
	MAXNODES = (MAXNODES * 2);
	Record* temp = new Record[nuovaDim];

	for (int i = 0; i < nuovaDim; i++)
	{
		temp[i].value = value_type();
		temp[i].used = false;
		temp[i].children.create();
	}

	int number;
	if (vecchiaDim < nuovaDim)
		number = vecchiaDim;
	else
		number = nuovaDim;

	for (int i = 0; i < number; i++)
	{
		temp[i].value = a[i].value;
		temp[i].used = a[i].used;
		temp[i].children = a[i].children;
	}

	delete[] a;
	a = temp;
}

#endif // _NARYTREECHILDLIST_H
