#ifndef _BSTP_H
#define _BSTP_H

#include "cellbst.h"
#include "BST.h"

// values are keys
// inserting 2 times the same value an exception will be thrown

template<class T>
class BST_pointer: public BST<T, Cell<T>*>
{
public:

	typedef typename BST<T, Cell<T>*>::value_type value_type;
	typedef typename BST<T, Cell<T>*>::node node;

	BST_pointer();
	BST_pointer(const value_type&);
	BST_pointer(const BST_pointer<T>&);
	~BST_pointer();

	BST_pointer<T>& operator =(const BST_pointer<T>&);

	bool empty() const; // true if the tree is empty
	void insert(value_type); // insert the element in the first available node (if it isn't already present in the tree)
	void erase(value_type); // erase the node with that value (values are key)

private:
	node tree_root;

	void create(); // create the binary tree
	node root() const; // return the root node
	node parent(node) const; // return the father of the node
	node left(node) const; // return the left node
	node right(node) const; // return the right node
	bool left_empty(node) const; // true if there isn't a left son
	bool right_empty(node) const; // true if there isn't a right son
	void erase(node); // erase the subtree having root in the node
	value_type read(node) const; // read the element in the node
	void write(node, value_type); // write the element in the node
	void ins_root(node); // insert the root
	void ins_left(node); // insert an empty node in the left son
	void ins_right(node); // insert an empty node in the right son

	bool isLeftSon(node) const; // true if the node is the left son of his parent
	bool isRightSon(node) const; // true if the node is the right son of his parent
};

template<class T>
BST_pointer<T>::BST_pointer()
{
	this->create();
}

template<class T>
BST_pointer<T>::BST_pointer(const value_type& value)
{
	this->create();
	node newroot = new Cell<value_type>(value);
	this->ins_root(newroot);
}

template<class T>
BST_pointer<T>::BST_pointer(const BST_pointer<T>& tree)
{
	*this = tree;
}

template<class T>
BST_pointer<T>::~BST_pointer()
{
	this->erase(this->root());
}

template<class T>
BST_pointer<T>& BST_pointer<T>::operator =(const BST_pointer<T>& tree)
{
	if (&tree != this) // avoid auto-assignment assignment
	{
		if (!this->empty())
			this->erase(this->root());

		node newroot = new Cell<value_type>;
		this->ins_root(newroot);
		node temp = this->root();
		this->ins_subtree(temp, tree, tree.root());
	}

	return *this;
}

template<class T>
bool BST_pointer<T>::empty() const
{
	return (tree_root == 0);
}

template<class T>
void BST_pointer<T>::insert(value_type val)
{
	if (this->empty())
	{
		node newroot;
		newroot = new Cell<value_type>;
		newroot->setValue(val);
		this->ins_root(newroot);
	}
	else //!empty
	{
		if (this->find(val))
			throw std::logic_error("BST (exception) - Unable to insert element (already present)");

		node curr = this->root();
		bool skip = false;

		do
		{
			if (val > this->read(curr))
			{
				if (this->right_empty(curr))
				{
					this->ins_right(curr);
					this->write(this->right(curr), val);
					skip = true;
				}
				else //!right_empty
				{
					curr = this->right(curr);
				}
			}
			else //val < read (curr)
			{
				if (this->left_empty(curr))
				{
					this->ins_left(curr);
					this->write(this->left(curr), val);
					skip = true;
				}
				else
				{
					curr = this->left(curr);
				}
			}
		} while (skip == false);
	}
}

template<class T>
void BST_pointer<T>::erase(value_type val)
{
	node n = this->getNode(val);

	if (this->is_leaf(n))
	{
		if (n != tree_root)
		{
			if (this->parent(n)->getRight() == n)
				this->parent(n)->setRight(0);
			else
				this->parent(n)->setLeft(0);
			delete n;
			n = 0;
		}
		else
		{
			delete tree_root;
			tree_root = 0;
		}
	}
	else if (this->left_empty(n) && !this->right_empty(n)) //1 son (left)
	{
		if (n != tree_root)
		{
			node p = this->parent(n), r_child = this->right(n); // save the parent

			// if n is on the right
			if (p->getRight() == n)
				p->setRight(r_child); // the new right child of the parent of n is the right-child of n
			else
				p->setLeft(r_child);

			r_child->setFather(p); // the parent of the right child of n is the parent of n
		}
		else
		{
			tree_root = this->right(n);
		}

		delete n;
		n = 0;
	}
	else if (!this->left_empty(n) && this->right_empty(n)) // 1 son (right)
	{
		if (n != tree_root)
		{
			node p = this->parent(n), l_child = this->left(n);

			if (p->getRight() == n)
				p->setRight(l_child);
			else
				p->setLeft(l_child);

			l_child->setFather(p);

		}
		else
		{
			tree_root = this->left(n);
		}

		delete n;
		n = 0;
	}
	else //2 sons
	{
		value_type minimum = this->min(right(n));
		node min = this->getNode(minimum);

		// it is not a leaf node, so we have to fix correctly this case
		if (!this->is_leaf(min) && this->parent(min)->getRight() == min)
			this->parent(min)->setRight(this->right(min));
		else
		{
			if (this->parent(min)->getRight() == min)
				this->parent(min)->setRight(0);
			else
				this->parent(min)->setLeft(0);
		}

		this->write(n, this->read(min)); // change the label of the n node
		delete min;
		min = 0;
	}
}

template<class T>
void BST_pointer<T>::create()
{
	tree_root = 0;
}

template<class T>
typename BST_pointer<T>::node BST_pointer<T>::root() const
{
	return tree_root;
}

template<class T>
typename BST_pointer<T>::node BST_pointer<T>::parent(node n) const
{
	if (n == this->root())
		throw std::logic_error("BST_pointer (exception) - Unable to get parent (node is root)");

	return n->getFather();
}

template<class T>
typename BST_pointer<T>::node BST_pointer<T>::left(node n) const
{
	if (this->left_empty(n))
		throw std::logic_error("BST_pointer (exception) - Unable to get left son");

	return n->getLeft();
}

template<class T>
typename BST_pointer<T>::node BST_pointer<T>::right(node n) const
{
	if (this->right_empty(n))
		throw std::logic_error("BST_pointer (exception) - Unable to get right son");

	return n->getRight();
}

template<class T>
bool BST_pointer<T>::left_empty(node n) const
{
	return (n->getLeft() == 0);
}

template<class T>
bool BST_pointer<T>::right_empty(node n) const
{
	return (n->getRight() == 0);
}

template<class T>
void BST_pointer<T>::erase(node n)
{
	if (!this->empty())
	{
		if (!is_leaf(n))
		{
			if (!this->left_empty(n))
				erase(n->getLeft());

			if (!this->right_empty(n))
				erase(n->getRight());
		}

		if (n != tree_root)
		{
			if (this->isLeftSon(n))
				(this->parent(n))->setLeft(0);
			else if (this->isRightSon(n))
				(this->parent(n))->setRight(0);
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
typename BST_pointer<T>::value_type BST_pointer<T>::read(node n) const
{
	if (n == 0)
		throw std::logic_error("BST_pointer (exception) - Unable to read value (invalid node)");

	return n->getValue();
}

template<class T>
void BST_pointer<T>::write(node n, value_type value)
{
	if (n == 0)
		throw std::logic_error("BST_pointer (exception) - Unable to write value (invalid node)");

	n->setValue(value);
}

template<class T>
void BST_pointer<T>::ins_root(node n = 0)
{
	if (n == 0)
		tree_root = new Cell<value_type>;
	else
	{
		tree_root = new Cell<value_type>;
		tree_root->setValue(n->getValue());
	}
}

template<class T>
void BST_pointer<T>::ins_left(node n)
{
	if (!this->left_empty(n))
		throw std::logic_error("BST_pointer (exception) - Unable to insert left node (already present)");

	node son;
	son = new Cell<value_type>;
	son->setFather(n);
	n->setLeft(son);
}

template<class T>
void BST_pointer<T>::ins_right(node n)
{
	if (!this->right_empty(n))
		throw std::logic_error("BST_pointer (exception) - Unable to insert right node (already present)");

	node son;
	son = new Cell<value_type>;
	son->setFather(n);
	n->setRight(son);
}

template<class T>
bool BST_pointer<T>::isLeftSon(node n) const
{
	if (n == 0 || n == this->root())
		throw std::logic_error("BST_pointer (exception) - Unable to establish if node is left son");

	return (n == (n->getFather())->getLeft());
}

template<class T>
bool BST_pointer<T>::isRightSon(node n) const
{
	if (n == 0 || n == this->root())
		throw std::logic_error("BST_pointer (exception) - Unable to establish if node is right son");

	return (n == (n->getFather())->getRight());
}

#endif // _BSTP_H
