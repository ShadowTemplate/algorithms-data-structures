#include "huffman.h"

using std::cout;
using std::endl;

int main()
{
	List_pointer<Pair> occurrences;
	Graph_list<Pair, int> huffmanGraph; // graph of pairs; edges are 0, 1

	occurrences = getOccurr(); // analyse the text and acquire frequencies

	cout << "Text has been analysed. Here is the result:" << endl;
	for (List_pointer<Pair>::position p = occurrences.begin(); !occurrences.end(p); p = occurrences.next(p))
		cout << endl << occurrences.read(p);

	cout << endl << endl;

	buildGraph(huffmanGraph, occurrences);

	assignWeight(huffmanGraph);

	List_pointer<EncodedPair> encodedList = getCodes(huffmanGraph, occurrences);

	cout << "Encoded letters:" << endl;
	for(List_pointer<EncodedPair>::position p = encodedList.begin(); !encodedList.end(p); p = encodedList.next(p))
		cout << endl << encodedList.read(p);

	compareResults(encodedList);

}
