#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template<class T>
vector<T> quicksort(vector<T> array)
{
	if (array.size() <= 1) // if the array has 0 or 1 element is already ordered
		return array;

	unsigned int pivot_index = array.size() / 2; // choose pivot
	T pivot_value = array[pivot_index];

	vector<T> smallerValues;
	vector<T> greaterValues;

	for (unsigned int i = 0; i < array.size(); i++)
		if (i != pivot_index)
		{
			if (array[i] <= pivot_value)
				smallerValues.push_back(array[i]);
			else
				greaterValues.push_back(array[i]);
		}

	vector<T> smallerOrdered = quicksort(smallerValues);
	vector<T> greaterOrdered = quicksort(greaterValues);
	vector<T> result;
	result.insert(result.end(), smallerOrdered.begin(), smallerOrdered.end()); // copy the smaller sorted part
	result.push_back(pivot_value);
	result.insert(result.end(), greaterOrdered.begin(), greaterOrdered.end()); // copy the greater sorted part

	return result;
}

int main()
{
	vector<int> array;

	array.push_back(8);
	array.push_back(10);
	array.push_back(3);
	array.push_back(7);
	array.push_back(11);
	array.push_back(6);
	array.push_back(4);
	array.push_back(1);
	array.push_back(9);
	array.push_back(2);
	array.push_back(5);

	vector<int> sortedArray = quicksort(array);

	cout << "Unsorted array:";
	cout << endl;
	for (vector<int>::iterator it = array.begin(); it != array.end(); it++)
		cout << *it << " ";
	cout << endl;

	cout << "Sorted array:";
	cout << endl;
	for (vector<int>::iterator it = sortedArray.begin(); it != sortedArray.end(); it++)
		cout << *it << " ";
	cout << endl;

}
