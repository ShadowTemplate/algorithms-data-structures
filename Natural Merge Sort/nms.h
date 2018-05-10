#ifndef _NATURALMERGESORT_H
#define _NATURALMERGESORT_H

#include <list>
using std::list;

template<class T>
bool sorted(list<T>& L)
{
	if (L.empty())
		return true;

	typename list<T>::iterator it = L.begin();
	typename list<T>::iterator it2 = L.begin();

	for (it2++; it2 != L.end(); it2++)
	{
		if (*it > *it2)
			return false;
		it++;
	}

	return true;
}

template<class T>
void NMS(list<T>& L)
{
	if (!sorted(L))
	{
		list<T> list1;
		list<T> list2;
		int currList = 1;

		T temp = L.front();
		L.pop_front();
		list1.push_back(temp);

		while (!L.empty())
		{
			if (L.front() < temp) // we have to switch the current list
			{
				if (currList == 1)
					currList = 2;
				else //currList == 2
					currList = 1;
			}

			temp = L.front();
			L.pop_front();

			if (currList == 1)
				list1.push_back(temp);
			else
				list2.push_back(temp);

		}

		NMS(list1);
		NMS(list2);

		while (!list1.empty() && !list2.empty())
		{
			if (list1.front() < list2.front())
			{
				L.push_back(list1.front());
				list1.pop_front();
			}
			else
			{
				L.push_back(list2.front());
				list2.pop_front();
			}
		}

		while (!list1.empty())
		{
			L.push_back(list1.front());
			list1.pop_front();
		}

		while (!list2.empty())
		{
			L.push_back(list2.front());
			list2.pop_front();
		}
	}
}

#endif // _NATURALMERGESORT_H
