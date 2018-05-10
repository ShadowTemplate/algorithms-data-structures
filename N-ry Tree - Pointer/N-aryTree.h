#ifndef _NARYTREE_H_
#define _NARYTREE_H_

#include <iostream>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <numeric>

using std::cout;
using std::ostream;
using std::endl;
using std::vector;
using std::accumulate;

template<class T, class N>
class NaryTree
{
public:
	typedef T value_type;
	typedef N node;

	virtual ~NaryTree()
	{
	}

	virtual void create() = 0; // create the binary tree
	virtual bool empty() const = 0; // true if the three is empty
	virtual void ins_root(node) = 0; // insert the root
	virtual node root() const = 0; // return the root node
	virtual node parent(const node&) const = 0; // return the father of the node
	virtual bool is_leaf(const node&) const = 0; // true if the node is a leaf
	virtual node firstChild(const node&) const = 0; // return the first child of the node
	virtual bool lastSibling(const node&) const = 0; // true if the node doesn't have a right sibling
	virtual node nextSibling(const node&) const = 0; // return the right sibling of the node
	virtual void insFirstSubTree(node, const NaryTree<value_type, node>&) = 0; // add the tree like the first child of the node
	virtual void insSubTree(node, const NaryTree<value_type, node>&) = 0; // add the tree like sibling of the node
	virtual void erase(node) = 0; // erase the subtree having root = node
	virtual value_type read(const node&) const = 0; // read the element in the node
	virtual void write(node, const value_type&) = 0; // write the element in the node

	bool operator ==(const NaryTree<value_type, node>&) const;
	bool operator !=(const NaryTree<value_type, node>&) const;

	void printSubTree(const node, ostream&) const; // useful for operator <<
	int numChild(const node) const; // return the number of children of the node
	void swapNodes(node, node); // swap the two nodes
	int size() const; // return the numbers of nodes of the tree
	int size(const node) const; // return the number of descendants of the node
	bool find(const value_type&) const; // true if the element is present in the tree
	value_type min() const; // return the minimum element of the tree
	value_type max() const; // return the maximum element of the tree
	int gradeN() const; // return the grade of the tree
	int height() const; // return the height of the tree
	void eraseLeaves(const value_type&); // erase the leaves having the same value of the function
	vector<node> evenRoots() const; // return an array of nodes. Every node have children whose sum is an even value
	vector<node> oddRoots() const; // return an array of nodes. Every node have children whose sum is an odd value
	vector<value_type> elementsArray() const; // return a vector with the elements of the tree
	void elementsArray(const node&, vector<value_type>&) const; // auxiliary for elementsArray
	vector<node> nodesArray() const; // return a vector with the nodes of the tree
	void nodesArray(const node&, vector<node>&) const; // auxiliary for nodesArray
	int numberLeaves() const; // return the number of leaves in the tree
	bool findOnPath(node, const value_type&) const; // true if the element is present in the path from root to the node
	bool findOnChildren(node, const value_type&) const; // true if the element is present in one of the children
	value_type pathSum(node) const; // return the sum of the element on the path from the root to the node
	vector<value_type> pathElements(node) const; // return a vector of the elements in the path from the root to the node

	void preorder() const;
	void inorder() const; // symmetric
	void postorder() const;
	void breadth() const;
	void preorder(const node&) const;
	void postorder(const node&) const;
	void inorder(const node&) const;
	void breadth(const node&) const;

private:
	bool checkEquality(const node&, const NaryTree<T, N>&, const node&) const;
	int height(const node&) const; // return the height of the tree starting from the node
	void eraseLeaves(const value_type&, node&); // erase the leaves having a certain value from the subtree having root in the node
};

template<class T, class N>
ostream& operator <<(ostream& out, const NaryTree<T, N>& tree)
{
	if (!tree.empty())
		tree.printSubTree(tree.root(), out);
	else
		out << "Empty Tree";

	out << endl;

	return out;
}

template<class T, class N>
bool NaryTree<T, N>::operator ==(const NaryTree<T, N>& t2) const
{
	if ((t2.empty() + this->empty()) == 2) //if ( !this->empty() && !t2.empty() )
		return true;
	if (this->size() != t2.size())
		return false;

	return checkEquality(this->root(), t2, t2.root());
}

template<class T, class N>
bool NaryTree<T, N>::operator !=(const NaryTree<T, N>& tree2) const
{
	return (!(*this == tree2));
}

template<class T, class N>
void NaryTree<T, N>::printSubTree(const node n, ostream& out) const
{
	out << "[ " << this->read(n);

	if (!this->is_leaf(n))
	{
		node temp;
		out << ": ";
		for (temp = this->firstChild(n); !this->lastSibling(temp); temp = this->nextSibling(temp))
		{
			this->printSubTree(temp, out);
			out << ", ";
		}

		this->printSubTree(temp, out);

	}

	out << " ]";
}

template<class T, class N>
int NaryTree<T, N>::numChild(const node n) const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception) - Unable to get number of children (empty tree)");

	if (this->is_leaf(n))
		return 0;

	node temp = this->firstChild(n);
	int counter = 0;

	while (!this->lastSibling(temp))
	{
		counter++;
		temp = this->nextSibling(temp);
	}

	counter++; //the last sibling wasn't counted

	return counter;
}

template<class T, class N>
void NaryTree<T, N>::swapNodes(node n1, node n2)
{
	if (this->read(n1) != this->read(n2))
	{
		value_type temp = this->read(n1);

		this->write(n1, this->read(n2));
		this->write(n2, temp);
	}
}

template<class T, class N>
int NaryTree<T, N>::size() const
{
	if (this->empty())
		return 0;

	return (this->size(this->root()) + 1);
}

template<class T, class N>
int NaryTree<T, N>::size(const node n) const
{
	int num = 0;
	node curr = n;
	std::deque<node> nodes;

	nodes.push_back(curr);

	while (!nodes.empty())
	{
		curr = nodes.front();
		num = num + this->numChild(curr);

		if (!this->is_leaf(curr))
		{
			node temp = this->firstChild(curr);
			for (int i = 0; i < this->numChild(curr) - 1; i++)
			{
				nodes.push_back(temp);
				temp = this->nextSibling(temp);
			}
			nodes.push_back(temp);
		}

		nodes.pop_front();
	}

	return num;
}

template<class T, class N>
bool NaryTree<T, N>::find(const value_type& val) const
{
	vector<value_type> elements = this->elementsArray();

	for (typename vector<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
		if (*it == val)
			return true;

	return false;
}

template<class T, class N>
typename NaryTree<T, N>::value_type NaryTree<T, N>::min() const
{
	vector<value_type> elements = this->elementsArray();

	if (elements.empty())
		throw std::logic_error("BinTree (exception) - Unable to retrieve minimum (empty tree)");

	value_type min = elements.front();

	for (typename vector<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
		if (*it < min)
			min = *it;

	return min;
}

template<class T, class N>
typename NaryTree<T, N>::value_type NaryTree<T, N>::max() const
{
	vector<value_type> elements = this->elementsArray();

	if (elements.empty())
		throw std::logic_error("BinTree (exception) - Unable to retrieve maximum (empty tree)");

	value_type max = elements.front();

	for (typename vector<value_type>::iterator it = elements.begin(); it != elements.end(); it++)
		if (*it > max)
			max = *it;

	return max;
}

template<class T, class N>
int NaryTree<T, N>::gradeN() const
{
	vector<node> nodes = nodesArray();

	if (nodes.empty())
		throw std::logic_error("BinTree (exception) - Unable to retrieve grade (empty tree)");

	int grade = this->numChild(nodes.front());

	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if (this->numChild(*it) > grade)
			grade = this->numChild(*it);

	return grade;
}

template<class T, class N>
int NaryTree<T, N>::height() const
{
	return (this->height(this->root()));
}

template<class T, class N>
void NaryTree<T, N>::eraseLeaves(const value_type& val)
{
	if (this->empty())
		throw std::logic_error("BinTree (exception) - Unable to erase leaves (empty tree)");

	node n = this->root();
	this->eraseLeaves(val, n);
}

template<class T, class N>
vector<N> NaryTree<T, N>::evenRoots() const
{
	vector<node> evenRoots;
	vector<node> nodes = this->nodesArray();
	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		vector<T> temp;
		this->elementsArray(*it, temp);
		if (((accumulate(temp.begin(), temp.end(), 0)) % 2) == 0)
			evenRoots.push_back(*it);
	}

	return evenRoots;
}

template<class T, class N>
vector<N> NaryTree<T, N>::oddRoots() const
{
	vector<node> oddRoots;
	vector<node> nodes = this->nodesArray();
	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		vector<T> temp;
		this->elementsArray(*it, temp);
		if (((accumulate(temp.begin(), temp.end(), 0)) % 2) != 0)
			oddRoots.push_back(*it);
	}

	return oddRoots;
}

template<class T, class N>
vector<T> NaryTree<T, N>::elementsArray() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception) - Unable to return vector (empty tree)");

	vector<value_type> elements;

	node temp = this->root();
	elements.push_back(this->read(temp));

	if (!this->is_leaf(temp))
	{
		node curr = this->firstChild(temp);

		for (int i = 0; i < this->numChild(temp) - 1; i++)
		{
			this->elementsArray(curr, elements);
			curr = this->nextSibling(curr);
		}

		this->elementsArray(curr, elements);
	}

	return elements;
}

template<class T, class N>
void NaryTree<T, N>::elementsArray(const node& n, vector<value_type>& elements) const
{
	elements.push_back(this->read(n));

	if (!this->is_leaf(n))
	{
		node curr = this->firstChild(n);

		for (int i = 0; i < this->numChild(n) - 1; i++)
		{
			this->elementsArray(curr, elements);
			curr = this->nextSibling(curr);
		}

		this->elementsArray(curr, elements);
	}
}

template<class T, class N>
vector<N> NaryTree<T, N>::nodesArray() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception) - Unable to return vector (empty tree)");

	vector<node> nodes;

	node temp = this->root();
	nodes.push_back(temp);

	if (!this->is_leaf(temp))
	{
		node curr = this->firstChild(temp);

		for (int i = 0; i < this->numChild(temp) - 1; i++)
		{
			this->nodesArray(curr, nodes);
			curr = this->nextSibling(curr);
		}

		this->nodesArray(curr, nodes);
	}

	return nodes;
}

template<class T, class N>
void NaryTree<T, N>::nodesArray(const node& n, vector<node>& nodes) const
{
	nodes.push_back(n);

	if (!this->is_leaf(n))
	{
		node curr = this->firstChild(n);

		for (int i = 0; i < this->numChild(n) - 1; i++)
		{
			this->nodesArray(curr, nodes);
			curr = this->nextSibling(curr);
		}

		this->nodesArray(curr, nodes);
	}
}

template<class T, class N>
int NaryTree<T, N>::numberLeaves() const
{
	int counter = 0;
	vector<node> nodes = this->nodesArray();
	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if (this->is_leaf(*it))
			counter++;

	return counter;
}

template<class T, class N>
bool NaryTree<T, N>::findOnPath(node currNode, const value_type& val) const
{
	if (currNode->getValue() == val)
		return true;

	while (currNode != this->root())
	{
		currNode = this->parent(currNode);
		if (currNode->getValue() == val)
			return true;
	}

	return false;
}

template<class T, class N>
bool NaryTree<T, N>::findOnChildren(node currNode, const value_type& val) const
{
	if (this->is_leaf(currNode))
		return false;

	currNode = this->firstChild(currNode);

	if (currNode->getValue() == val)
		return true;

	while (!this->lastSibling(currNode))
	{
		currNode = this->nextSibling(currNode);
		if (currNode->getValue() == val)
			return true;
	}

	return false;
}

template<class T, class N>
T NaryTree<T, N>::pathSum(node currNode) const
{
	value_type counter = value_type();

	counter += currNode->getValue();

	while (currNode != this->root())
	{
		currNode = this->parent(currNode);
		counter += currNode->getValue();
	}

	return counter;
}

template<class T, class N>
vector<typename NaryTree<T, N>::value_type> NaryTree<T, N>::pathElements(node currNode) const
{
	vector<value_type> elements;

	elements.push_back(currNode->getValue());
	while (currNode != this->root())
	{
		currNode = this->parent(currNode);
		elements.push_back(currNode->getValue());
	}

	return elements;
}

template<class T, class N>
void NaryTree<T, N>::preorder() const
{
	if (this->empty())
		throw std::logic_error("NaryTree (exception) - Unable to perform pre-order visit (empty tree)");

	this->preorder(this->root());
}

template<class T, class N>
void NaryTree<T, N>::inorder() const
{
	if (this->empty())
		throw std::logic_error("NaryTree (exception) - Unable to perform in-order visit (empty tree)");

	this->inorder(this->root());
}

template<class T, class N>
void NaryTree<T, N>::postorder() const
{
	if (this->empty())
		throw std::logic_error("NaryTree (exception) - Unable to perform post-order visit (empty tree)");

	this->postorder(this->root());
}

template<class T, class N>
void NaryTree<T, N>::breadth() const
{
	if (this->empty())
		throw std::logic_error("NaryTree (exception) - Unable to perform breadth visit (empty tree)");

	this->breadth(this->root());
}

template<class T, class N>
void NaryTree<T, N>::preorder(const node& n) const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception) - Unable to perform pre-order visit (empty tree)");

	cout << this->read(n) << " ";

	if (!this->is_leaf(n))
	{
		node temp = this->firstChild(n);

		for (int i = 0; i < this->numChild(n) - 1; i++)
		{
			this->preorder(temp);
			temp = this->nextSibling(temp);
		}
		this->preorder(temp);
	}
}

template<class T, class N>
void NaryTree<T, N>::postorder(const node& n) const
{
	if (this->is_leaf(n))
		cout << this->read(n) << " ";
	else
	{
		node temp = this->firstChild(n);
		while (!this->lastSibling(temp))
		{
			this->postorder(temp);
			temp = this->nextSibling(temp);
		}
		this->postorder(temp);
		cout << this->read(n) << " ";
	}
}

template<class T, class N>
void NaryTree<T, N>::inorder(const node& n) const
{
	if (this->is_leaf(n))
		cout << this->read(n) << " ";
	else
	{
		node temp = this->firstChild(n);
		this->inorder(temp);
		cout << this->read(n) << " ";
		while (!this->lastSibling(temp))
		{
			temp = this->nextSibling(temp);
			this->inorder(temp);
		}
	}
}

template<class T, class N>
void NaryTree<T, N>::breadth(const node& n) const
{
	node temp = 0;
	std::deque<node> nodes;

	nodes.push_back(n);

	while (!nodes.empty())
	{
		temp = nodes.front();
		cout << this->read(temp) << " ";
		nodes.pop_front();

		if (!this->is_leaf(temp))
		{
			node curr = this->firstChild(temp);
			while (!this->lastSibling(curr))
			{
				nodes.push_back(curr);
				curr = this->nextSibling(curr);
			}
			nodes.push_back(curr);
		}
	}
}

template<class T, class N>
bool NaryTree<T, N>::checkEquality(const N& n1, const NaryTree<T, N>& t2, const N& n2) const
{
	if (this->read(n1) != t2.read(n2))
		return false;

	if (this->numChild(n1) != t2.numChild(n2))
		return false;

	if (!this->is_leaf(n1) && !t2.is_leaf(n2))
	{
		node temp1 = this->firstChild(n1);
		node temp2 = t2.firstChild(n2);

		while (!this->lastSibling(temp1))
		{
			if (this->checkEquality(temp1, t2, temp2))
			{
				temp1 = this->nextSibling(temp1);
				temp2 = t2.nextSibling(temp2);
			}
			else
				return false;
		}

		return this->checkEquality(temp1, t2, temp2);
	}

	return true;
}

template<class T, class N>
int NaryTree<T, N>::height(const node& n) const
{
	if (this->empty())
		throw std::logic_error("NaryTree (exception) - Unable to retrieve height of the tree (empty tree)");

	if (this->is_leaf(n))
		return 1;
	else
	{
		vector<int> heights;
		node curr = this->firstChild(n);
		while (!this->lastSibling(curr))
		{
			int currHeight = 0;
			currHeight = this->height(curr);
			heights.push_back(currHeight);
			curr = this->nextSibling(curr);
		}

		int currHeight = 0;
		currHeight = this->height(curr);
		heights.push_back(currHeight);

		int maxHeight = heights.front();

		for (vector<int>::iterator it = heights.begin(); it != heights.end(); it++)
			if (*it > maxHeight)
				maxHeight = *it;

		return maxHeight + 1;
	}
}

template<class T, class N>
void NaryTree<T, N>::eraseLeaves(const value_type& val, node& n)
{
	if (!this->is_leaf(n))
	{
		node curr = this->firstChild(n);
		while (!this->lastSibling(curr))
		{
			this->eraseLeaves(val, curr);
			curr = this->nextSibling(curr);
		}
		this->eraseLeaves(val, curr);
	}
	else if (this->read(n) == val)
		this->erase(n);
}

#endif /* _NARYTREE_H_ */
