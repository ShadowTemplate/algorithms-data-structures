#ifndef _NODE_H
#define _NODE_H

class Node
{
public:
	Node()
	{
		ID = -1;
	}

	Node(const Node& node2)
	{
		*this = node2;
	}

	Node& operator =(const Node& node2)
	{
		if (&node2 != this) // avoid auto-assignment
		{
			this->ID = node2.ID;
		}
		return *this;
	}

	~Node()
	{
	}

	bool operator ==(const Node& n2) const
	{
		return (this->ID == n2.ID);
	}

	bool operator !=(const Node& n2) const
	{
		return (!(*this == n2));
	}

	void setID(const int newID)
	{
		ID = newID;
	}

	int getID() const
	{
		return ID;
	}

private:
	int ID;
};

ostream& operator <<(ostream& out, const Node& node)
{
	out << " [ID ";
	out << node.getID();
	out << "]";
	return out;
}

#endif // _NODE_H
