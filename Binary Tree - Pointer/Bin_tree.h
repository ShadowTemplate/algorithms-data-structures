#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <iostream>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::vector;

template<class T, class N>
class BinTree
{
public:
	typedef T value_type;
	typedef N node;

	virtual ~BinTree()
	{
	}

	virtual void create() = 0; // create the binary tree
	virtual bool empty() const = 0; // true if the tree is empty
	virtual node root() const = 0; // return the root node
	virtual node parent(node) const = 0; // return the father of the node
	virtual node left(node) const = 0; // return the left son
	virtual node right(node) const = 0; // return the right son
	virtual bool left_empty(node) const = 0; // true if there isn't a left son
	virtual bool right_empty(node) const = 0; // true if there isn't a right son
	virtual void erase(node) = 0; // erase the subtree having root = node
	virtual value_type read(node) const = 0; // read the element in the node
	virtual void write(node, value_type) = 0; // write the element in the node
	virtual void ins_root(node) = 0; // insert the root
	virtual void ins_left(node) = 0; // insert an empty node in the left son
	virtual void ins_right(node) = 0; // insert an empty node in the right son

	bool operator ==(const BinTree<T, N>&) const;
	bool operator !=(const BinTree<T, N>&) const;

	void printSubTree(const node, ostream&) const;
	bool is_leaf(const node) const; // true if the node is a leaf
	int size() const; // return the numbers of nodes of the tree
	bool find(const value_type&) const; // true if the element is present in the tree
	int height() const; // return the height of the tree
	void epurateLeaves(const value_type&); // erases the leafs having the same value of the function
	void swap_node(node, node); // swap the values of the two nodes
	value_type min() const; // return the minimum value of tree
	value_type max() const; // return the maximum value of tree
	void ins_subtree(node&, const BinTree<T, N>&, node); // insert a subtree: node must be a leaf; the 2nd tree not empty
	void build(const BinTree<T, N>&, const BinTree<T, N>&); // build a new tree: implicit tree must be empty; the other two mustn't.
	bool hasSubTree(const BinTree<T, N>&); // true if the parameter tree is a subtree of the implicit tree
	vector<value_type> elementsArray() const;
	vector<node> nodesArray() const;
	int numberLeaves() const;

	void preorder() const;
	void inorder() const; //symmetric
	void postorder() const;
	void breadth() const;
	void preorder(const node&) const;
	void inorder(const node&) const; //symmetric
	void postorder(const node&) const;
	void breadth(const node&) const;

private:
	// recursion-needed methods
	int size(const node&) const; // return the number of descendants of the node
	bool find(const node&, const value_type&) const; // true if the element is present in the node or in it's subtree
	int height(const node&) const; // return the height of the tree having root in the node
	void epurateLeaves(node, const value_type&); // erases the leafs having a certain value from the subtree having root in the node
	value_type min(const node&) const; // return the minimum in the subtree having root in the node
	value_type max(const node&) const; // return the maximum in the subtree having root in the node
	bool hasSubTree(const node&, const BinTree<T, N>&, const node&) const; // true if the parameter tree is a subtree of the implicit tree
	vector<node> findOccurrences(const value_type&); // return an array of nodes whose values are equal to the parameter
	void elementsArray(const node&, vector<value_type>&) const;
	void nodesArray(const node&, vector<node>&) const;
};

template<class T, class N>
ostream& operator <<(ostream& out, const BinTree<T, N>& tree)
{
	if (!tree.empty())
		tree.printSubTree(tree.root(), out);
	else
		out << "Empty Tree" << endl;

	out << endl;
	return out;
}

template<class T, class N>
bool BinTree<T, N>::operator ==(const BinTree<T, N>& t) const
{
	std::stringstream tree1, tree2;

	tree1 << *this;
	tree2 << t;

	return (tree1.str() == tree2.str());
}

template<class T, class N>
bool BinTree<T, N>::operator !=(const BinTree<T, N>& tree2) const
{
	return (!(*this == tree2));
}

template<class T, class N>
void BinTree<T, N>::printSubTree(const node n, ostream& out) const
{
	out << "[" << this->read(n) << ", ";

	if (!this->left_empty(n))
		this->printSubTree(this->left(n), out);
	else
		out << "NIL";

	out << ", ";

	if (!this->right_empty(n))
		this->printSubTree(this->right(n), out);
	else
		out << "NIL";

	out << " ]";
}

template<class T, class N>
bool BinTree<T, N>::is_leaf(const node n) const
{
	return (this->left_empty(n) && this->right_empty(n));
}

template<class T, class N>
int BinTree<T, N>::size() const
{
	if (this->empty())
		return 0;

	return (this->size(this->root()) + 1);
}

template<class T, class N>
bool BinTree<T, N>::find(const value_type& val) const
{
	return (this->find(this->root(), val));
}

template<class T, class N>
int BinTree<T, N>::height() const
{
	return (this->height(this->root()));
}

template<class T, class N>
void BinTree<T, N>::epurateLeaves(const value_type& val)
{
	this->epurateLeaves(this->root(), val);
}

template<class T, class N>
void BinTree<T, N>::swap_node(node n1, node n2)
{
	if ( n1 == 0 || n2 == 0 )
		throw std::logic_error("BinTree (exception)");

	if (this->read(n1) != this->read(n2))
	{
		value_type temp = this->read(n1);
		this->write(n1, this->read(n2));
		this->write(n2, temp);
	}
}

template<class T, class N>
typename BinTree<T, N>::value_type BinTree<T, N>::min() const
{
	return (this->min(this->root()));
}

template<class T, class N>
typename BinTree<T, N>::value_type BinTree<T, N>::max() const
{
	return (this->max(this->root()));
}

template<class T, class N>
void BinTree<T, N>::ins_subtree(node& n1, const BinTree<T, N>& t, node n2)
{
	if (t.empty() || !this->is_leaf(n1))
		throw std::logic_error("BinTree (exception)");

	this->write(n1, t.read(n2));

	if (!t.left_empty(n2))
	{
		this->ins_left(n1);
		node temp = this->left(n1);
		this->ins_subtree(temp, t, t.left(n2));
	}

	if (!t.right_empty(n2))
	{
		this->ins_right(n1);
		node temp = this->right(n1);
		this->ins_subtree(temp, t, t.right(n2));
	}
}

template<class T, class N>
void BinTree<T, N>::build(const BinTree<T, N>& t1, const BinTree<T, N>& t2)
{
	if (!this->empty() || t1.empty() || t2.empty())
		throw std::logic_error("BinTree (exception)");

	node n = 0;
	this->ins_root(n);
	n = this->root();
	this->ins_left(n);
	this->ins_right(n);
	node temp = this->left(n);
	this->ins_subtree(temp, t1, t1.root());
	temp = this->right(n);
	this->ins_subtree(temp, t2, t2.root());
}

template<class T, class N>
bool BinTree<T, N>::hasSubTree(const BinTree<T, N>& t2)
{
	if (t2.empty())
		return true;

	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	//1st !empty e 2nd !empty
	if (this->size() < t2.size())
		return false;

	//1st !empty >= 2nd !empty
	if (t2.size() == 1 && this->find(t2.read(t2.root())))
		return true;
	if (t2.size() == 1 && !this->find(t2.read(t2.root())))
		return false;

	//1st !empty >= 2nd (>1)
	vector<node> nodes = this->findOccurrences(t2.read(t2.root()));

	bool flag = 0;
	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end() && !flag; it++)
		flag = flag + hasSubTree(*it, t2, t2.root());

	return flag;
}

template<class T, class N>
vector<T> BinTree<T, N>::elementsArray() const
{
	vector<T> elements;
	if (!this->empty())
		elementsArray(this->root(), elements);

	return elements;
}

template<class T, class N>
vector<N> BinTree<T, N>::nodesArray() const
{
	vector<N> nodes;
	if (!this->empty())
		nodesArray(this->root(), nodes);

	return nodes;
}

template<class T, class N>
int BinTree<T, N>::numberLeaves() const
{
	int counter = 0;
	vector<node> nodes = this->nodesArray();

	for (typename vector<node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if (this->is_leaf(*it))
			counter++;

	return counter;
}

template<class T, class N>
void BinTree<T, N>::preorder() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	this->preorder(this->root());
}

template<class T, class N>
void BinTree<T, N>::inorder() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	this->inorder(this->root());
}

template<class T, class N>
void BinTree<T, N>::postorder() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	this->postorder(this->root());
}

template<class T, class N>
void BinTree<T, N>::breadth() const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	this->breadth(this->root());
}

template<class T, class N>
void BinTree<T, N>::preorder(const node& n) const
{
	cout << this->read(n);

	if (!this->left_empty(n))
		this->preorder(this->left(n));

	if (!this->right_empty(n))
		this->preorder(this->right(n));
}

template<class T, class N>
void BinTree<T, N>::inorder(const node& n) const //symmetric
{
	if (!this->left_empty(n))
		this->inorder(this->left(n));

	cout << this->read(n);

	if (!this->right_empty(n))
		this->inorder(this->right(n));
}

template<class T, class N>
void BinTree<T, N>::postorder(const node& n) const
{
	if (!this->left_empty(n))
		this->postorder(this->left(n));

	if (!this->right_empty(n))
		this->postorder(this->right(n));

	cout << this->read(n);
}

template<class T, class N>
void BinTree<T, N>::breadth(const node& n) const
{
	node temp = 0;
	std::deque<node> nodes;

	nodes.push_back(n);

	while (!nodes.empty())
	{
		temp = nodes.front();
		cout << this->read(temp) << " ";
		nodes.pop_front();

		if (!this->left_empty(temp))
			nodes.push_back(this->left(temp));

		if (!this->right_empty(temp))
			nodes.push_back(this->right(temp));
	}
}

template<class T, class N>
int BinTree<T, N>::size(const node& n) const
{
	int num = 0;
	node curr = n;
	std::deque<node> nodes;

	nodes.push_back(curr);

	while (!nodes.empty())
	{
		curr = nodes.front();
		num++;

		if (!this->left_empty(curr))
			nodes.push_back(this->left(curr));

		if (!this->right_empty(curr))
			nodes.push_back(this->right(curr));

		nodes.pop_front();
	}

	num--; // the starting node must not be counted
	return num;
}

template<class T, class N>
bool BinTree<T, N>::find(const node& n, const value_type& val) const
{
	if (this->read(n) == val)
		return true;

	if (!this->left_empty(n) && !this->right_empty(n))
		return (this->find(this->left(n), val) || this->find(this->right(n), val));

	if (!this->left_empty(n) && this->right_empty(n))
		return (this->find(this->left(n), val));

	if (this->left_empty(n) && !this->right_empty(n))
		return (this->find(this->right(n), val));

	return false;
}

template<class T, class N>
int BinTree<T, N>::height(const node& n) const
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	if (this->is_leaf(n))
		return 1; // or 0... depends..
	else
	{
		int leftDepth = 0;
		int rightDepth = 0;

		// find each depth
		if (!this->left_empty(n))
			leftDepth = this->height(n->getLeft());
		if (!this->right_empty(n))
			rightDepth = this->height(n->getRight());

		// use the biggest one
		if (leftDepth > rightDepth)
			return (leftDepth + 1);
		else
			return (rightDepth + 1);
	}
}

template<class T, class N>
void BinTree<T, N>::epurateLeaves(node n, const value_type& val)
{
	if (this->empty())
		throw std::logic_error("BinTree (exception)");

	if (!this->is_leaf(n))
	{
		if (!this->left_empty(n))
			this->epurateLeaves(n->getLeft(), val);
		if (!this->right_empty(n))
			this->epurateLeaves(n->getRight(), val);
	}
	else
	{
		if (this->read(n) == val)
			this->erase(n);
	}
}

template<class T, class N>
typename BinTree<T, N>::value_type BinTree<T, N>::min(const node& n) const
{
	if (this->is_leaf(n))
		return (this->read(n));
	else
	{
		if (!this->left_empty(n) && !this->right_empty(n))
			return (this->read(n) < this->min(this->left(n)) ? (
					this->read(n) < this->min(this->right(n)) ? this->read(n) : this->min(this->right(n))) : (
					this->min(this->right(n)) < this->min(this->left(n)) ? this->min(this->right(n)) : this->min(this->left(n)))); //return minimum between read(n), min(left(n)) and min(right(n))

		if (!this->left_empty(n) && this->right_empty(n))
			return (this->read(n) < this->min(this->left(n)) ? this->read(n) : this->min(this->left(n))); //return minimum between read(n) and min(left(n))

		if (this->left_empty(n) && !this->right_empty(n))
			return (this->read(n) < this->min(this->right(n)) ? this->read(n) : this->min(this->right(n))); //return minimum between read(n) and min(right(n))
	}
	throw std::logic_error("BinTree (exception)");
}

template<class T, class N>
typename BinTree<T, N>::value_type BinTree<T, N>::max(const node& n) const
{
	if (this->is_leaf(n))
		return (this->read(n));
	else
	{
		if (!this->left_empty(n) && !this->right_empty(n))
			return (this->read(n) > this->max(this->left(n)) ? (
					this->max(this->right(n)) > this->read(n) ? this->max(this->right(n)) : this->read(n)) : (
					this->max(this->right(n)) > this->max(this->left(n)) ? this->max(this->right(n)) : this->max(this->left(n)))); //return maximum between read(n), max(left(n)) and max(right(n))

		if (!this->left_empty(n) && this->right_empty(n))
			return (this->read(n) > this->max(this->left(n)) ? this->read(n) : this->max(this->left(n))); //return maximum between read(n) and max(left(n))

		if (this->left_empty(n) && !this->right_empty(n))
			return (this->read(n) > this->max(this->right(n)) ? this->read(n) : this->max(this->right(n))); //return maximum between read(n) and max(right(n))
	}
	throw std::logic_error("BinTree (exception)");
}

template<class T, class N>
bool BinTree<T, N>::hasSubTree(const node& n1, const BinTree<T, N>& t2, const node& n2) const
{
	if (!t2.left_empty(n2) && this->left_empty(n1))
		return false;

	if (!t2.right_empty(n2) && this->right_empty(n1))
		return false;

	//Have same number of children
	if ((this->is_leaf(n1) && t2.is_leaf(n2)) && (this->read(n1) == t2.read(n2)))
		return true;
	if ((this->is_leaf(n1) && t2.is_leaf(n2)) && (this->read(n1) != t2.read(n2)))
		return false;

	if ((!this->left_empty(n1)) && (!t2.left_empty(n2) && t2.right_empty(n2)))
		return (this->hasSubTree(this->left(n1), t2, t2.left(n2)));

	if ((!this->right_empty(n1)) && (t2.left_empty(n2) && !t2.right_empty(n2)))
		return (this->hasSubTree(this->right(n1), t2, t2.right(n2)));

	if ((!this->left_empty(n1) && !this->right_empty(n1)) && (!t2.left_empty(n2) && !t2.right_empty(n2)))
		return (this->hasSubTree(this->left(n1), t2, t2.left(n2)) && this->hasSubTree(this->right(n1), t2, t2.right(n2)));

	return false;
}

template<class T, class N>
vector<N> BinTree<T, N>::findOccurrences(const value_type& val)
{
	vector<node> occurrences;

	if (!this->empty())
	{
		node temp = this->root();
		std::deque<node> nodes;

		nodes.push_back(temp);

		while (!nodes.empty())
		{
			temp = nodes.front();

			if (val == this->read(temp))
				occurrences.push_back(temp);

			nodes.pop_front();

			if (!this->left_empty(temp))
				nodes.push_back(this->left(temp));

			if (!this->right_empty(temp))
				nodes.push_back(this->right(temp));
		}

	}
	return occurrences;
}

template<class T, class N>
void BinTree<T, N>::elementsArray(const node& n, vector<value_type>& elements) const
{
	elements.push_back(this->read(n));

	if (!this->left_empty(n))
		elementsArray(this->left(n), elements);

	if (!this->right_empty(n))
		elementsArray(this->right(n), elements);
}

template<class T, class N>
void BinTree<T, N>::nodesArray(const node& n, vector<node>& nodes) const
{
	nodes.push_back(n);

	if (!this->left_empty(n))
		nodesArray(this->left(n), nodes);

	if (!this->right_empty(n))
		nodesArray(this->right(n), nodes);
}

#endif /* _BINTREE_H_ */
