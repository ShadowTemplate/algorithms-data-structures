#ifndef _GRAPHACOLORING_H
#define _GRAPHCOLORING_H

#include <list>
#include <string>
#include <stdexcept>

#include "Graph.h"

using std::list;
using std::string;

typedef string colour;

class Palette
{
public:
	list<colour> palette;
	unsigned int size;

	Palette(const unsigned int newSize)
	{
		size = newSize;
	}

	Palette(const Palette& newPalette)
	{
		*this = newPalette;
	}

	Palette& operator =(const Palette& newPalette)
	{
		if (&newPalette != this) // avoid auto-assignment
		{
			this->size = newPalette.size;
			this->palette = newPalette.palette;
		}
		return *this;
	}

	~Palette()
	{
	}

	void addColour(colour newColour)
	{
		if (palette.size() < size)
			palette.push_back(newColour);
		else
			throw std::logic_error("Palette (exception) - Unable to add colour (full palette)");
	}
};

template<class N, class W>
bool isAvailableColour(Graph<N, colour, W>& graph, colour currColour, typename Graph<N, colour, W>::node& currNode) // true if the colour isn't used by the adjacent nodes
{
	list<typename Graph<N, colour, W>::node> nodes = graph.adjacents(currNode);
	list<colour> adjColour;
	for (typename list<typename Graph<N, colour, W>::node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		adjColour.push_back(graph.getLabel(*it));
	if (std::find(adjColour.begin(), adjColour.end(), currColour) == adjColour.end())
		return true;

	return false;
}

template<class N, class W>
bool completelyColoured(Graph<N, colour, W>& graph, Palette& currPal) // true if every node has a label present in the palette
{
	list<typename Graph<N, colour, W>::node> nodes = graph.nodesList();
	for (typename list<typename Graph<N, colour, W>::node>::iterator it = nodes.begin(); it != nodes.end(); it++)
		if (std::find(currPal.palette.begin(), currPal.palette.end(), graph.getLabel(*it)) == currPal.palette.end())
			return false;

	return true;
}

template<class N, class W>
bool notColouredNode(Graph<N, colour, W>& graph, Palette& currPal, typename Graph<N, colour, W>::node& currNode) // true if the label of the node isn't present in the palette
{
	if (std::find(currPal.palette.begin(), currPal.palette.end(), graph.getLabel(currNode)) == currPal.palette.end())
		return true;

	return false;
}

template<class N, class W>
void graphColour(Graph<N, colour, W>& graph, Palette& currPal, typename Graph<N, colour, W>::node& currNode)
{
	static bool endFlag = false; // true if all the nodes are coloured

	typename list<colour>::iterator it;
	for (it = currPal.palette.begin(); (it != currPal.palette.end() && !completelyColoured(graph, currPal)); it++) // for every colour (and until there are some uncoloured nodes)
		if (isAvailableColour(graph, *it, currNode)) // if there is a colour unused by adjacent nodes
		{
			graph.setLabel(currNode, *it); // put the colour in the current node
			if (!completelyColoured(graph, currPal)) // if there are other nodes to be coloured
			{
				list<typename Graph<N, colour, W>::node> nodes = graph.nodesList();
				bool flag = true;
				for (typename list<typename Graph<N, colour, W>::node>::iterator it2 = nodes.begin();
						it2 != nodes.end() && flag; it2++)
					if (notColouredNode(graph, currPal, *it2)) // find the first uncoloured node
					{
						flag = false; // the first uncoloured node has been found
						graphColour(graph, currPal, *it2); // recursive-call
					}
			}
			else
				endFlag = true; // set the flag true (algorithm will terminate)
		}

	if (it == currPal.palette.end() && !endFlag) // if the aren't any available colours for the node, clear is label
		graph.setLabel(currNode, colour()); // backtrack method will assign another colour to the previous node
}

#endif // _GRAPHCOLORING_H
