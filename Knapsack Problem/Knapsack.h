#ifndef _KNAPSACK_H
#define _KNAPSACK_H

#include <iostream>
#include <algorithm>
#include "Bag.h"

using std::cout;
using std::cin;

template<class T, class N>
void getItems(vector<Item<T, N> >& items)
{
	int flag = 1;
	int counter = 1;

	do
	{
		Item<T, N> currItem;
		cout << "Insert item name: ";
		getline(cin, currItem.name);
		cout << "Insert item value: ";
		cin >> currItem.value;
		cout << "Insert item weight: ";
		cin >> currItem.weight;
		currItem.ID = counter;

		items.push_back(currItem);
		counter++;

		cout << "Press 1 to add an item or 0 to start algorithm: ";
		cin >> flag;
		cin.ignore();
		cout << endl;
	} while (flag);
}

template<class T, class N>
void printItems(vector<Item<T, N> >& items)
{
	cout << "Items:" << endl;

	for (typename vector<Item<T, N> >::iterator it = items.begin(); it != items.end(); it++)
	{
		cout << (*it).name << " - Value: " << (*it).value << " - Weight: " << (*it).weight << " - ID: " << (*it).ID;
		cout << endl;
	}

}

template<class T, class N>
void buildTree(Bag<T, N>& bag, vector<Item<T, N> >& items, typename NaryTree_pointer<Item<T, N> >::node currNode)
{
	for (typename vector<Item<T, N> >::iterator it = items.begin(); it != items.end(); it++)
		if (!bag.config.findOnPath(currNode, *it) // the element hasn't already been added in the previous step
		&& !bag.config.findOnChildren(currNode, *it) // avoid adding the same element on two different branches
		&& (predictWeight(bag, currNode, *it) <= bag.maxWeight)) // check if the budget is exceeded
		{
			bag.config.insLastChild(currNode);
			typename NaryTree_pointer<Item<T, N> >::node newSon = bag.config.firstChild(currNode);
			while (!bag.config.lastSibling(newSon))
				newSon = bag.config.nextSibling(newSon);
			newSon->setValue(*it);
			buildTree(bag, items, newSon);
		}
}

template<class T, class N>
N predictWeight(Bag<T, N>& bag, typename NaryTree_pointer<Item<T, N> >::node currNode, Item<T, N>& item)
{
	N counter = N();

	counter += currNode->getValue().weight;

	while (currNode != bag.config.root())
	{
		currNode = bag.config.parent(currNode);
		counter += currNode->getValue().weight;
	}

	counter += item.weight;

	return counter;
}

template<class T, class N>
vector<vector<Item<T, N> > > findBestConfig(Bag<T, N>& bag)
{
	vector<vector<Item<T, N> > > solutions;
	vector<typename NaryTree_pointer<Item<T, N> >::node> bagNodes = bag.config.nodesArray();
	vector<T> sums;

	for (typename vector<typename NaryTree_pointer<Item<T, N> >::node>::iterator it = bagNodes.begin();
			it != bagNodes.end(); it++)
		if (bag.config.is_leaf(*it)) // for each path
			sums.push_back(getValuesSum(bag, *it)); // store the sum

	cout << "Found sums: ";
	for (typename vector<T>::iterator it = sums.begin(); it != sums.end(); it++)
		cout << *it << " ";
	cout << endl;

	bag.maxSum = sums.front();
	for (typename vector<T>::iterator it = sums.begin(); it != sums.end(); it++) // find the highest sum
		if (bag.maxSum < *it)
			bag.maxSum = *it;

	cout << endl << "Best sum: " << bag.maxSum;

	for (typename vector<typename NaryTree_pointer<Item<T, N> >::node>::iterator it = bagNodes.begin();
			it != bagNodes.end(); it++) // for each node of the tree
		if (bag.config.is_leaf(*it) && (getValuesSum(bag, *it) == bag.maxSum)) // if is a leaf and is the best path
			solutions.push_back(bag.config.pathElements(*it)); // store the paths with highest sum

	return solutions;
}

template<class T, class N>
T getValuesSum(Bag<T, N>& bag, typename NaryTree_pointer<Item<T, N> >::node currNode)
{
	T counter = T();

	counter += currNode->getValue().value;

	while (currNode != bag.config.root())
	{
		currNode = bag.config.parent(currNode);
		counter += currNode->getValue().value;
	}

	return counter;
}

template<class T, class N>
void epuratePermutations(vector<vector<Item<T, N> > >& solutions)
{
	vector<vector<Item<T, N> > > epurateSolutions;
	int counter = 0;

	typename vector<vector<Item<T, N> > >::iterator it = solutions.begin();

	epurateSolutions.push_back(*it); // the first is always good
	for (it++; it != solutions.end(); it++) // from the second to the last solution
	{
		for (typename vector<vector<Item<T, N> > >::iterator it2 = epurateSolutions.begin();
				it2 != epurateSolutions.end(); it2++)
			counter += isPermutation(*it, *it2); // check if it's a permutation of one of the solutions in the vector

		if (counter == 0) // it's not a permutation
			epurateSolutions.push_back(*it);

		counter = 0;
	}

	while (!solutions.empty())
		solutions.pop_back();

	solutions = epurateSolutions;
}

template<class T, class N>
bool isPermutation(vector<Item<T, N> >& v1, vector<Item<T, N> >& v2)
{
	if (v1.size() != v2.size())
		return false;

	unsigned int counter = 0;

	for (typename vector<Item<T, N> >::iterator it = v1.begin(); it != v1.end(); it++)
		for (typename vector<Item<T, N> >::iterator it2 = v2.begin(); it2 != v2.end(); it2++)
			counter += (*it == *it2); // count the number of elements in common

	if (counter != v1.size()) // if it's a permutation, the number of elements in common is = v1.size()
		return false;

	return true;
}

template<class T, class N>
vector<Item<T, N> > findGreedySolution(Bag<T, N> bag, vector<Item<T, N> > items)
{
	std::sort(items.begin(), items.end()); // check out operator < for items to understand sort

	N currWeight = N();

	vector<Item<T, N> > solution;

	for (typename vector<Item<T, N> >::iterator it = items.begin(); it != items.end(); it++)
		if ((currWeight + (*it).weight) <= bag.maxWeight)
		{
			currWeight += (*it).weight;
			solution.push_back(*it);
		}

	return solution;
}

#endif // _KNAPSACK_H
