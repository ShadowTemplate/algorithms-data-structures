#ifndef _NARYTREEP_H
#define _NARYTREEP_H

#include "cellnt.h"
#include "N-aryTree.h"
#include <vector>

template<class T>
class NaryTree_pointer: public NaryTree<T, Cell<T>*>
{
public:
	typedef typename NaryTree<T, Cell<T>*>::value_type value_type;
	typedef typename NaryTree<T, Cell<T>*>::node node;

	NaryTree_pointer();
	NaryTree_pointer(const value_type&);
	NaryTree_pointer(const NaryTree_pointer<T>&);
	~NaryTree_pointer();

	NaryTree_pointer<T>& operator =(const NaryTree_pointer<T>&);

	bool empty() const; // true if the three is empty
	void ins_root(node); // insert the root
	node root() const; // return the root node
	node parent(const node&) const; // return the father of the node
	bool is_leaf(const node&) const; // true if the node is a leaf
	node firstChild(const node&) const; // return the first child of the node
	bool lastSibling(const node&) const; // true if the node doesn't have a right sibling
	node nextSibling(const node&) const; // return the right sibling of the node
	void insFirstSubTree(node, const NaryTree<value_type, node>&); // add the tree like the first child of the node (node!=0)
	void insSubTree(node, const NaryTree<value_type, node>&); // add the tree like sibling of the node (node!=0)
	void erase(node); // erase the subtree having root = node
	value_type read(const node&) const; // read the element in the node
	void write(node, const value_type&); // write the element in the node

	node lastChild(const node) const; // return the last child of the node
	bool firstSibling(const node) const; // true if the node is the first child
	node prevSibling(const node) const; // return the left sibling of the node
	void insFirstChild(node); // add a child to the node (leftmost)
	void insLastChild(node); // add a child to the node (rightmost)
	void insRightSibling(node); // add a right sibling to the node
	void build(NaryTree_pointer<T>, NaryTree_pointer<T>); // build a new tree: implicit tree must be empty, other two !empty
	void erase(); // erase the all tree

private:
	node tree_root;

	void create(); // create the binary tree
	void copyTree(node, const NaryTree_pointer<T>&, node); // insert, starting from the node (created and empty), the tree
	void copyAbstractTree(node&, const NaryTree<value_type, node>&, const node&); // insert, starting from the node (created and empty), the tree
};

template<class T>
NaryTree_pointer<T>::NaryTree_pointer()
{
	this->create();
}

template<class T>
NaryTree_pointer<T>::NaryTree_pointer(const value_type& value)
{
	this->create();
	node newroot = new Cell<value_type>(value);
	this->ins_root(newroot);
}

template<class T>
NaryTree_pointer<T>::NaryTree_pointer(const NaryTree_pointer<T>& tree)
{
	this->create();
	*this = tree;
}

template<class T>
NaryTree_pointer<T>::~NaryTree_pointer()
{
	this->erase(this->root());
}

template<class T>
NaryTree_pointer<T>& NaryTree_pointer<T>::operator =(const NaryTree_pointer<T>& tree)
{
	if (&tree != this) // avoid auto-assignment
	{
		if (!this->empty())
			this->erase(this->root());
			
		if (tree.root() != 0)
		{
			node newroot = new Cell<value_type>;
			this->ins_root(newroot);
			this->copyTree(this->root(), tree, tree.root());
		}
		else
			tree_root = 0;
	}
	return *this;
}

template<class T>
void NaryTree_pointer<T>::copyTree(node n1, const NaryTree_pointer<T>& t2, node n2)
{
	this->write(n1, t2.read(n2));

	if (!t2.is_leaf(n2))
	{
		node temp;
		for (temp = t2.firstChild(n2); !t2.lastSibling(temp); temp = t2.nextSibling(temp))
		{
			this->insLastChild(n1);
			this->copyTree(this->lastChild(n1), t2, temp);
		}

		//insert the last sibling
		this->insLastChild(n1);
		this->copyTree(lastChild(n1), t2, temp);
	}
}

template<class T>
void NaryTree_pointer<T>::create()
{
	tree_root = 0;
}

template<class T>
bool NaryTree_pointer<T>::empty() const
{
	return (this->root() == 0);
}

template<class T>
void NaryTree_pointer<T>::ins_root(node n)
{
	if (n == 0)
		tree_root = new Cell<value_type>;
	else
		tree_root = new Cell<value_type>(n->getValue());
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::root() const
{
	return tree_root;
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::parent(const node& n) const
{
	if (n == this->root())
		throw std::logic_error("NaryTree_pointer (exception) - Unable to retrieve parent (node is root)");

	return n->getFather();
}

template<class T>
bool NaryTree_pointer<T>::is_leaf(const node& n) const
{
	if (n == 0)
		throw std::logic_error("NaryTree_pointer (exception)");

	return (n->getChild() == 0);
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::firstChild(const node& n) const
{
	if (this->is_leaf(n))
		throw std::logic_error("NaryTree_pointer (exception) - Unable to retrieve first child (node is leaf)");

	return (n->getChild());
}

template<class T>
bool NaryTree_pointer<T>::lastSibling(const node& n) const
{
	if (this->is_leaf(this->parent(n)))
		throw std::logic_error("NaryTree_pointer (exception) - Unable to check if node is last sibling");

	return (n == this->lastChild(this->parent(n)) ? true : false);
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::nextSibling(const node& n) const
{
	if (this->lastSibling(n))
		throw std::logic_error("NaryTree_pointer (exception) - Unable to get next sibling (node is last sibling)");

	return n->getRight();
}


template<class T>
void NaryTree_pointer<T>::insFirstSubTree(node n, const NaryTree<value_type, node>& t2)
{
	if (n == 0 || t2.empty())
		throw std::logic_error("NaryTree_pointer (exception) - Unable to insert subtree");

	this->insFirstChild(n);
	node temp = this->firstChild(n);
	node root = t2.root();
	this->copyAbstractTree(temp, t2, root);
}

template<class T>
void NaryTree_pointer<T>::insSubTree(node n, const NaryTree<value_type, node>& t2)
{
	if (n == 0 || t2.empty() || n == this->root())
		throw std::logic_error("NaryTree_pointer (exception) - Unable to insert subtree");

	this->insRightSibling(n);
	node temp = this->nextSibling(n);
	node root = t2.root();
	this->copyAbstractTree(temp, t2, root);
}


template<class T>
void NaryTree_pointer<T>::erase(node n)
{
	if (!this->empty())
	{
		if (!this->is_leaf(n))
		{
			node curr = this->lastChild(n);
			while (curr != this->firstChild(n))
			{
				node temp2 = curr;
				curr = this->prevSibling(curr);
				this->erase(temp2);
			}
			this->erase(curr);
		}
		if (n != tree_root)
		{
			if (this->size(this->parent(n)) == 1) // last child
				(this->parent(n))->setChild(0);

			if (n->getLeft() != 0)
				(n->getLeft())->setRight(n->getRight());

			if (n->getRight() != 0)
				(n->getRight())->setLeft(n->getLeft());

			delete n;
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
typename NaryTree<T, Cell<T>*>::value_type NaryTree_pointer<T>::read(const node& n) const
{
	if (n == 0)
		throw std::logic_error("NaryTree_pointer (exception) - Unable to read label (invalid node)");

	return n->getValue();
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::lastChild(const node n) const
{
	node temp = firstChild(n);
	while (temp->getRight() != 0)
		temp = temp->getRight();

	return temp;
}

template<class T>
void NaryTree_pointer<T>::write(node n, const value_type& value)
{
	if (n == 0)
		throw std::logic_error("NaryTree_pointer (exception) - Unable to write label (invalid node)");

	n->setValue(value);
}

template<class T>
bool NaryTree_pointer<T>::firstSibling(const node n) const
{
	return (n == (this->parent(n))->getChild() ? true : false);
}

template<class T>
typename NaryTree_pointer<T>::node NaryTree_pointer<T>::prevSibling(const node n) const
{
	if (this->firstSibling(n))
		throw std::logic_error("NaryTree_pointer (exception) - Unable to retrieve previous sibling (node is first sibling)");

	return n->getLeft();
}

template<class T>
void NaryTree_pointer<T>::insFirstChild(node n)
{
	if (n == 0)
		throw std::logic_error("NaryTree_pointer (exception) - Unable to insert child (invalid node)");

	node son = new Cell<value_type>;

	if (!this->is_leaf(n))
	{
		(this->firstChild(n))->setLeft(son);
		son->setRight(this->firstChild(n));
	}

	son->setFather(n);
	n->setChild(son);
}

template<class T>
void NaryTree_pointer<T>::insLastChild(node n)
{
	if (n == 0)
		throw std::logic_error("NaryTree_pointer (exception) - Unable to insert child (invalid node)");

	node son = new Cell<value_type>;

	if (!this->is_leaf(n))
	{
		node temp = this->lastChild(n);
		(this->lastChild(n))->setRight(son);
		son->setLeft(temp);
	}

	if (this->is_leaf(n))
		n->setChild(son);

	son->setFather(n);
}

template<class T>
void NaryTree_pointer<T>::insRightSibling(node n)
{
	if (n == 0 || n == root())
		throw std::logic_error("NaryTree_pointer (exception) - Unable to insert child (invalid node)");

	if (this->lastSibling(n))
		this->insLastChild(this->parent(n));
	else
	{
		node brother = new Cell<value_type>;

		brother->setFather(parent(n));
		brother->setLeft(n);
		brother->setRight(nextSibling(n));

		(nextSibling(n))->setLeft(brother);

		n->setRight(brother);
	}
}

template<class T>
void NaryTree_pointer<T>::build(NaryTree_pointer<T> t1, NaryTree_pointer<T> t2)
{
	if (!this->empty() || t1.empty() || t2.empty())
		throw std::logic_error("NaryTree_pointer (exception) - Unable to build tree");

	node newroot = new Cell<value_type>(value_type());
	this->ins_root(newroot);
	node temp = this->root();
	this->insFirstSubTree(temp, t1);
	temp = this->firstChild(root());
	this->insSubTree(temp, t2);
}

template<class T>
void NaryTree_pointer<T>::copyAbstractTree(node& n1, const NaryTree<value_type, node>& t2, const node& n2)
{
	this->write(n1, t2.read(n2));

	if (!t2.is_leaf(n2))
	{
		node temp;
		for (temp = t2.firstChild(n2); !t2.lastSibling(temp); temp = t2.nextSibling(temp))
		{
			this->insLastChild(n1);
			node temp2 = this->lastChild(n1);
			this->copyAbstractTree(temp2, t2, temp);
		}

		//insert the last sibling
		this->insLastChild(n1);
		node temp2 = this->lastChild(n1);
		this->copyAbstractTree(temp2, t2, temp);
	}
}

template<class T>
void NaryTree_pointer<T>::erase( )
{
	this->erase(this->root());
}

#endif // _NARYTREE_H
