#ifndef _HEAPSORT_H_
#define _HEAPSORT_H_

#include "heap.h"

template<class T>
void heapSort(T vector[], const int len)
{
	Heap<T, T> heap(len);

	for (int i = 0; i < len; i++)
		heap.insert(vector[i], vector[i]);

	for (int i = 0; i < len; i++)
	{
		vector[i] = (heap.getMin()).getValue();
		heap.pop();
	}
}

#endif /* _HEAPSORT_H_ */
