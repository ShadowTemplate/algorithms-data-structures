#ifndef _BST_H_
#define _BST_H_

#include <iostream>
#include <deque>
#include <sstream>
#include <stdexcept>

using std::cout;
using std::endl;
using std::ostream;

template<class T, class N> //Values are keys
class BST
{
public:
	typedef T value_type;
	typedef N node;

	virtual ~BST()
	{
	}

	virtual void insert(value_type) = 0; // insert the element in the first available node (if it isn't already present in the tree)
	virtual void erase(value_type) = 0; // erase the node with that value (values are key)

	template<class X, class Y>
	friend ostream& operator<<(ostream &, const BST<X, Y>&);

	bool operator ==(const BST<T, N>&) const;
	bool operator !=(const BST<T, N>&) const;

	int size() const; // return the numbers of nodes of the tree
	bool find(const value_type&) const; // true if the element is present in the tree
	value_type min() const;
	value_type max() const;

	void preorder() const;
	void inorder() const; //symmetric
	void postorder() const;
	void breadth() const;

protected:
	virtual void create() = 0; // create the BST
	virtual bool empty() const = 0; // true if the tree is empty
	virtual node root() const = 0; // return the root node
	virtual node parent(node) const = 0; // return the father of the node
	virtual node left(node) const = 0; // return the left son
	virtual node right(node) const = 0; // return the right son
	virtual bool left_empty(node) const = 0; // true if there isn't a left son
	virtual bool right_empty(node) const = 0; // true if there isn't a right son
	virtual void erase(node) = 0; // erase the subtree having root in the node
	virtual value_type read(node) const = 0; // read the element in the node
	virtual void write(node, value_type) = 0; // write the element in the node
	virtual void ins_root(node) = 0; // insert the root
	virtual void ins_left(node) = 0; // insert an empty node in the left son
	virtual void ins_right(node) = 0; // insert an empty node in the right son

	void printSubTree(const node, ostream&) const; // useful for operator <<
	int height() const; // return the height of the tree
	bool is_leaf(const node) const; // true if the node is a leaf
	void ins_subtree(node&, const BST<T, N>&, node); // insert a subtree starting from the node
	int size(const node) const; // return the number of descendants of the node
	int height(const node) const; // return the height of the tree having root in the node
	node getNode(const value_type&) const; // return the node of the value
	value_type min(const node) const; // return the minimum in the subtree having root in the node

	void preorder(const node) const;
	void inorder(const node) const; // symmetric
	void postorder(const node) const;
	void breadth(const node) const;
};

template<class T, class N>
ostream& operator <<(ostream& out, const BST<T, N>& tree)
{
	if (!tree.empty())
		tree.printSubTree(tree.root(), out);
	else
		out << "Empty Tree" << endl;

	out << endl;

	return out;
}

template<class T, class N>
bool BST<T, N>::operator ==(const BST<T, N>& t) const
{
	std::stringstream tree1, tree2;

	tree1 << *this;
	tree2 << t;

	return (tree1.str() == tree2.str());
}

template<class T, class N>
bool BST<T, N>::operator !=(const BST<T, N>& tree2) const
{
	return (!(*this == tree2));
}

template<class T, class N>
void BST<T, N>::printSubTree(const node n, ostream& out) const
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
int BST<T, N>::size() const
{
	if (this->empty())
		return 0;

	return (this->size(this->root()) + 1);
}

template<class T, class N>
bool BST<T, N>::find(const value_type& val) const
{
	if (this->empty())
		return false;

	bool flag = false;
	bool skip = false;
	node curr = this->root();

	do
	{
		if (val == this->read(curr))
			flag = true;
		else if (val < this->read(curr))
		{
			if (!this->left_empty(curr))
				curr = this->left(curr);
			else
				skip = true;
		}
		else if (val > this->read(curr))
		{
			if (!this->right_empty(curr))
				curr = this->right(curr);
			else
				skip = true;
		}
	} while (flag == false && skip == false);

	return flag;
}

template<class T, class N>
int BST<T, N>::height() const
{
	if (this->empty())
		return 0;

	return (this->height(this->root()));
}

template<class T, class N>
typename BST<T, N>::value_type BST<T, N>::min() const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to retrieve minimum (empty tree)");

	value_type min = this->read(this->root());
	node curr = this->root();

	while (!this->left_empty(curr))
	{
		curr = this->left(curr);
		min = this->read(curr);
	}

	return min;
}

template<class T, class N>
typename BST<T, N>::value_type BST<T, N>::max() const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to retrieve maximum (empty tree)");

	value_type max = this->read(this->root());
	node curr = this->root();

	while (!this->right_empty(curr))
	{
		curr = this->right(curr);
		max = this->read(curr);
	}

	return max;
}

template<class T, class N>
void BST<T, N>::preorder() const
{
	this->preorder(this->root());
}

template<class T, class N>
void BST<T, N>::inorder() const
{
	this->inorder(this->root());
}

template<class T, class N>
void BST<T, N>::postorder() const
{
	this->postorder(this->root());
}

template<class T, class N>
void BST<T, N>::breadth() const
{
	this->breadth(this->root());
}

template<class T, class N>
bool BST<T, N>::is_leaf(const node n) const
{
	return (this->left_empty(n) && this->right_empty(n));
}

template<class T, class N>
void BST<T, N>::ins_subtree(node& n1, const BST<T, N>& t, node n2)
{
	if (t.empty() || !this->is_leaf(n1))
		throw std::logic_error("BST (exception) - Unable to insert subtree");

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
int BST<T, N>::size(const node n) const
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
int BST<T, N>::height(const node n) const
{
	if (this->empty())
		return 0;

	if (this->is_leaf(n))
		return 1;
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
typename BST<T, N>::node BST<T, N>::getNode(const value_type& val) const
{
	if (this->empty() || !this->find(val))
		throw std::logic_error("BST (exception) - Unable to retrieve node");

	node curr = this->root();
	bool skip = false;

	do
	{
		if (val == this->read(curr))
			skip = true;
		else if (val > this->read(curr))
			curr = this->right(curr);
		else if (val < this->read(curr))
			curr = this->left(curr);
	} while (skip == false);

	return curr;
}

template<class T, class N>
typename BST<T, N>::value_type BST<T, N>::min(const node n) const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to retrieve minimum (empty tree)");

	value_type min = this->read(n);
	node curr = n;

	while (!this->left_empty(curr))
	{
		curr = this->left(curr);
		min = this->read(curr);
	}

	return min;
}

template<class T, class N>
void BST<T, N>::preorder(const node n) const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to perform pre-order visit (empty tree)");

	cout << this->read(n);

	if (!this->left_empty(n))
		this->preorder(this->left(n));

	if (!this->right_empty(n))
		this->preorder(this->right(n));
}

template<class T, class N>
void BST<T, N>::inorder(const node n) const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to perform in-order visit (empty tree)");

	if (!this->left_empty(n))
		this->inorder(this->left(n));

	cout << this->read(n);

	if (!this->right_empty(n))
		this->inorder(this->right(n));
}

template<class T, class N>
void BST<T, N>::postorder(const node n) const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to perform post-order visit (empty tree)");

	if (!this->left_empty(n))
		this->postorder(this->left(n));

	if (!this->right_empty(n))
		this->postorder(this->right(n));

	cout << this->read(n);
}

template<class T, class N>
void BST<T, N>::breadth(const node n) const
{
	if (this->empty())
		throw std::logic_error("BST (exception) - Unable to perform breadth visit (empty tree)");

	node temp;
	std::deque<node> nodes;

	nodes.push_back(n);

	while (!nodes.empty())
	{
		temp = nodes.front();
		cout << this->read(temp);
		nodes.pop_front();

		if (!this->left_empty(temp))
			nodes.push_back(this->left(temp));

		if (!this->right_empty(temp))
			nodes.push_back(this->right(temp));
	}
}

#endif /* _BST_H_ */
