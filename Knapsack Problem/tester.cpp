#include "Knapsack.h"

int main()
{
	Bag<int, int> bag;
	vector<Item<int, int> > items;

	bag.maxWeight = 30;

	// procedure to acquire items via keyboard
	// getItems(items);

	Item<int, int> item1;
	Item<int, int> item2;
	Item<int, int> item3;
	Item<int, int> item4;
	Item<int, int> item5;
	Item<int, int> item6;

	item1.name = "Nokia Lumia";
	item1.value = 200;
	item1.weight = 30;
	item1.ID = 1;

	item2.name = "iPad Mini";
	item2.value = 150;
	item2.weight = 20;
	item2.ID = 2;

	item3.name = "HTC";
	item3.value = 130;
	item3.weight = 10;
	item3.ID = 3;

	item4.name = "iPhone";
	item4.value = 100;
	item4.weight = 10;
	item4.ID = 4;

	item5.name = "Samsung Galaxy";
	item5.value = 120;
	item5.weight = 10;
	item5.ID = 5;

	item6.name = "Blackberry";
	item6.value = 310;
	item6.weight = 21;
	item6.ID = 6;

	items.push_back(item1);
	items.push_back(item2);
	items.push_back(item3);
	items.push_back(item4);
	items.push_back(item5);
	items.push_back(item6);

	printItems(items);

	buildTree(bag, items, bag.config.root());
	cout << endl << "Bag configurations tree: " << endl << bag.config << endl;

	vector<vector<Item<int, int> > > solutions = findBestConfig(bag);

	epuratePermutations(solutions);

	cout << endl << "Best solution(s) is(are):" << endl;

	for (vector<vector<Item<int, int> > >::iterator it = solutions.begin(); it != solutions.end(); it++)
	{
		for (vector<Item<int, int> >::iterator it2 = (*it).begin(); it2 != (*it).end(); it2++)
			if (*it2 != Item<int, int>()) // hides the root
				cout << *it2 << endl;

		cout << endl;
	}

	vector<Item<int, int> > greedySolution;
	bag.maxSum = 0;
	greedySolution = findGreedySolution(bag, items);
	cout << endl << "Greedy solution is:" << endl;
	for (vector<Item<int, int> >::iterator it = greedySolution.begin(); it != greedySolution.end(); it++)
		cout << *it << endl;

	cout << endl;
}
