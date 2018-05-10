#ifndef _BINTREEP_H
#define _BINTREEP_H

#include "cellbt.h"
#include "Bin_tree.h"

template<class T>
class BinTree_pointer: public BinTree<T, Cell<T>*>
{
public:
	typedef typename BinTree<T, Cell<T>*>::value_type value_type;
	typedef typename BinTree<T, Cell<T>*>::node node;

	BinTree_pointer();
	BinTree_pointer(const value_type&); // root
	BinTree_pointer(const BinTree_pointer<T>&);
	~BinTree_pointer();

	BinTree_pointer<T>& operator =(const BinTree_pointer<T>&);

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

	void mutation(node, BinTree_pointer<T>&, node); // swap two subtrees from different trees
	bool isLeftSon(node) const; // true if the node is the left son of his parent
	bool isRightSon(node) const; // true if the node is the right son of his parent

private:
	node tree_root;
};

template<class T>
BinTree_pointer<T>::BinTree_pointer()
{
	this->create();
}

template<class T>
BinTree_pointer<T>::BinTree_pointer(const value_type& value)
{
	this->create();
	node newroot = new Cell<value_type>(value);
	this->ins_root(newroot);
}

template<class T>
BinTree_pointer<T>::BinTree_pointer(const BinTree_pointer<T>& tree)
{
	*this = tree;
}

template<class T>
BinTree_pointer<T>::~BinTree_pointer()
{
	this->erase(this->root());
}

template<class T>
BinTree_pointer<T>& BinTree_pointer<T>::operator =(const BinTree_pointer<T>& tree)
{
	if (&tree != this) // avoid auto-assignment
	{
		if (!this->empty())
			this->erase(this->root());

		node newroot = new Cell<value_type>;
		this->ins_root(newroot);
		newroot = this->root();
		this->ins_subtree(newroot, tree, tree.root());
	}

	return *this;
}

template<class T>
void BinTree_pointer<T>::create()
{
	tree_root = 0;
}

template<class T>
bool BinTree_pointer<T>::empty() const
{
	return (this->root() == 0);
}

template<class T>
typename BinTree_pointer<T>::node BinTree_pointer<T>::root() const
{
	return tree_root;
}

template<class T>
typename BinTree_pointer<T>::node BinTree_pointer<T>::parent(node n) const
{
	if (n == this->root())
		throw std::logic_error("BinTree_pointer (exception) - Unable to retrieve parent (node is root)");

	return n->getFather();
}

template<class T>
typename BinTree_pointer<T>::node BinTree_pointer<T>::left(node n) const
{
	if (this->left_empty(n))
		throw std::logic_error("BinTree_pointer (exception) - Unable to retrieve left son (node is left_empty)");

	return n->getLeft();
}

template<class T>
typename BinTree_pointer<T>::node BinTree_pointer<T>::right(node n) const
{
	if (this->right_empty(n))
		throw std::logic_error("BinTree_pointer (exception) - Unable to retrieve right son (node is right_empty)");

	return n->getRight();
}

template<class T>
bool BinTree_pointer<T>::left_empty(node n) const
{
	if (n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to check if node has a left son (invalid node)");

	return (n->getLeft() == 0);
}

template<class T>
bool BinTree_pointer<T>::right_empty(node n) const
{
	if (n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to check if node has a right son (invalid node)");

	return (n->getRight() == 0);
}

template<class T>
void BinTree_pointer<T>::erase(node n)
{
	if (!this->empty())
	{
		if (!this->is_leaf(n))
		{
			if (!this->left_empty(n))
				this->erase(n->getLeft());

			if (!this->right_empty(n))
				this->erase(n->getRight());
		}

		if (n != this->root())
		{
			if (this->isLeftSon(n))
				(parent(n))->setLeft(NULL);
			else if (isRightSon(n))
				(parent(n))->setRight(NULL);
			delete (n);
			n = 0;
		}
		else
		{
			delete tree_root;
			tree_root = 0;
		}
	}
}

template<class T>
typename BinTree<T, Cell<T>*>::value_type BinTree_pointer<T>::read(node n) const
{
	if (n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to read node (invalid node)");

	return n->getValue();
}

template<class T>
void BinTree_pointer<T>::write(node n, value_type value)
{
	if (n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to write the value in the node (invalid node)");

	n->setValue(value);
}

template<class T>
void BinTree_pointer<T>::ins_root(node n = 0)
{
	if (n == 0)
		tree_root = new Cell<value_type>;
	else
		tree_root = new Cell<value_type>(n->getValue());
}

template<class T>
void BinTree_pointer<T>::ins_left(node n)
{
	if (!this->left_empty(n) || n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to insert left son");

	node son = new Cell<value_type>;
	son->setFather(n);
	n->setLeft(son);
}

template<class T>
void BinTree_pointer<T>::ins_right(node n)
{
	if (!this->right_empty(n) || n == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to insert right son");

	node son = new Cell<value_type>;
	son->setFather(n);
	n->setRight(son);
}

template<class T>
void BinTree_pointer<T>::mutation(node n1, BinTree_pointer<T>& tree2, node n2)
{
	if (n1 == 0 || n2 == 0)
		throw std::logic_error("BinTree_pointer (exception) - Unable to perform mutation (invalid node)");

	BinTree_pointer temp(0);

	temp.ins_subtree(temp.root(), *this, n1);

	if (!this->left_empty(n1))
		this->erase(n1->getLeft());
	if (!this->right_empty(n1))
		this->erase(n1->getRight());

	this->ins_subtree(n1, tree2, n2);

	if (!tree2.left_empty(n2))
		tree2.erase(n2->getLeft());
	if (!tree2.right_empty(n2))
		tree2.erase(n2->getRight());
	tree2.ins_subtree(n2, temp, temp.root());
}

template<class T>
bool BinTree_pointer<T>::isLeftSon(node n) const
{
	if (n == 0 || n == this->root())
		throw std::logic_error("BinTree_pointer (exception) - Unable to check if node is left son");

	return (n == (n->getFather())->getLeft());
}

template<class T>
bool BinTree_pointer<T>::isRightSon(node n) const
{
	if (n == 0 || n == this->root())
		throw std::logic_error("BinTree_pointer (exception) - Unable to check if node is right son");

	return (n == (n->getFather())->getRight());
}

#endif // _BINTREEP_H
