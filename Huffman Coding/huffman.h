#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_

#include "set_pointer.h"
#include "heap.h"
#include "Graph_list.h"
#include <fstream>
#include <string>

using std::ios;
using std::fstream;
using std::list;
using std::ostream;
using std::string;

struct Pair
{
	char letter;
	int occurr;

	Pair(char newLetter = char(), int newOccurr = int())
	{
		letter = newLetter;
		occurr = newOccurr;
	}
};

ostream& operator <<(ostream& os, const Pair& p)
{
	if(p.letter != '\n')
		os << "Char: " << p.letter << " - Occurrences: " << p.occurr;
	else
		os << "Char: RETURN - Occurrences: " << p.occurr;

	return os;
}

struct EncodedPair
{
	char letter;
	int occurr;
	string code;

	EncodedPair(char newLetter = char(), int newOccurr = int(), string newCode = string())
	{
		letter = newLetter;
		occurr = newOccurr;
		code = newCode;
	}
};

ostream& operator <<(ostream& os, const EncodedPair& p)
{
	if(p.letter != '\n')
		os << "Char: " << p.letter << " - String: (" << p.code << ")";
	else
		os << "Char: RETURN - String: (" << p.code << ")";

	return os;
}

List_pointer<Pair> getOccurr()
{
	List_pointer<Pair> occurrences; // list of pair
	Set_pointer<char> characters; // set of characters that have already been read

	fstream f1;
	f1.open("text.txt", ios::in); // open the file in read mode

	if (!f1)
		throw std::logic_error("Unable to open text.txt");

	char c;
	while (!f1.eof())
	{
		c = f1.get();
		if (c != EOF && !characters.find(c)) // we have read a new character (and the text isn't completely analysed)
		{
			characters.insert(c); // add the character that has just been read
			occurrences.push_back(Pair(c, 1));
		}
		else if (c != EOF) // we have re-read a character (and the text isn't completely analysed)
		{
			bool flag = true;
			for (List_pointer<Pair>::position p = occurrences.begin(); flag; p = occurrences.next(p)) // iterate on the list until the character has been found
				if (occurrences.read(p).letter == c)
				{
					Pair temp = occurrences.read(p);
					temp.occurr++; // increase the number of occurrences
					occurrences.write(temp, p); // update the value
					flag = false;
				}
		}
	}
	f1.close();

	return occurrences;
}

void buildGraph(Graph_list<Pair, int>& graph, List_pointer<Pair> occurrences)
{
	Heap<Graph_list<Pair, int>::node, int> priQueue;

	while (!occurrences.empty()) // convert the list of pairs in a priority queue of nodes of the graph
	{
		Pair tempPair = occurrences.read(occurrences.begin()); // first pair of the list
		occurrences.pop_front();

		Graph_list<Pair, int>::node tempNode;
		graph.insNode(tempNode);
		graph.setLabel(tempNode, tempPair);

		priQueue.insert(tempNode, tempPair.occurr);
	}

	while (priQueue.size() != 1) // when there is only one node the graph has been built
	{
		// acquire the two pairs with lowest frequency
		Graph_list<Pair, int>::node min1 = priQueue.getMin().getValue();
		priQueue.pop();
		Graph_list<Pair, int>::node min2 = priQueue.getMin().getValue();
		priQueue.pop();

		// add to the graph a new node, having 2 sons (the 2 pairs)
		// the label will be a pair ( \b as char, sum of frequencies as number of occurrences)
		Graph_list<Pair, int>::node temp;
		graph.insNode(temp);
		int freq = graph.getLabel(min1).occurr + graph.getLabel(min2).occurr;
		graph.setLabel(temp, Pair('\b', freq));
		graph.insEdge(temp, min1);
		graph.insEdge(temp, min2);

		// add the node to the queue
		priQueue.insert(temp, freq);
	}
}

void assignWeight(Graph_list<Pair, int>& graph)
{
	list<Graph_list<Pair, int>::node> nodes = graph.nodesList();

	for (list<Graph_list<Pair, int>::node>::iterator it = nodes.begin(); it != nodes.end(); it++)
	{
		// we know that adjacent nodes list will be made up of 0 or 2 elements (graph is a tree)
		list<Graph_list<Pair, int>::node> adjTemp = graph.adjacents(*it);
		if (adjTemp.size() != 0)
		{
			graph.setWeight(*it, adjTemp.front(), 0); // we set 0 on the firt adjacent node
			graph.setWeight(*it, adjTemp.back(), 1); // and 1 on the other adjacent node
		}
	}
}

string getString(Graph_list<Pair, int>& graph, char c)
{
	string code; // code of the char

	Graph_list<Pair, int>::node nodeC; // node of the character
	list<Graph_list<Pair, int>::node> nodes = graph.nodesList();
	Graph_list<Pair, int>::node root = nodes.back(); // we know that the root is the last element added in the graph

	bool flag = true;
	for (list<Graph_list<Pair, int>::node>::iterator it = nodes.begin(); flag; it++)
		if (graph.getLabel(*it).letter == c)
		{
			flag = false;
			nodeC = *it;
		}

	nodes.clear();

	nodes = graph.getPath(root, nodeC);
	for (list<Graph_list<Pair, int>::node>::iterator it = nodes.begin(), it2 = it; it2 != nodes.end(); it++)
	{
		it2++;
		if (graph.isEdge(*it, *it2))
		{
			char temp = (graph.getWeight(*it, *it2) + '0'); // we convert the weight (0 or 1) in the char 0 or 1
			code.push_back(temp);
		}
	}

	return code;
}

List_pointer<EncodedPair> getCodes(Graph_list<Pair, int>& graph, List_pointer<Pair> occurrences)
{
	List_pointer<EncodedPair> encodedList;

	// first we insert letter and frequency (without the encoded string)
	for (List_pointer<Pair>::position p = occurrences.begin(); !occurrences.end(p); p = occurrences.next(p))
		encodedList.push_back(EncodedPair(occurrences.read(p).letter, occurrences.read(p).occurr));

	// now we add the encoded string
	for (List_pointer<EncodedPair>::position p = encodedList.begin(); !encodedList.end(p); p = encodedList.next(p))
	{
		char c = encodedList.read(p).letter;
		int occurr = encodedList.read(p).occurr;
		encodedList.write(EncodedPair(c, occurr, getString(graph, c)), p); // update the EncodedPair
	}

	return encodedList;
}

void compareResults(List_pointer<EncodedPair>& encodedList)
{
	float numChars = 0; // number of characters in the text
	float numBit = 0; // number of bits needed with Huffman encoding system

	for (List_pointer<EncodedPair>::position p = encodedList.begin(); !encodedList.end(p); p = encodedList.next(p))
		numChars += encodedList.read(p).occurr;

	for (List_pointer<EncodedPair>::position p = encodedList.begin(); !encodedList.end(p); p = encodedList.next(p))
	{
		float temp = encodedList.read(p).occurr / numChars; // percentage of appearance
		numBit += (temp * encodedList.read(p).code.length());
	}

	numBit = numBit * numChars;

	cout << endl << endl;

	cout << "# bit needed with ASCII encoding: " << 8 * numChars << endl;
	cout << "# bit needed with Huffman encoding: " << numBit;
}

#endif /* _HUFFMAN_H_ */

