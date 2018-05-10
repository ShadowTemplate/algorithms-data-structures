#ifndef _MINMAX_H
#define _MINMAX_H

template<class T>
struct Pair
{
	typedef T value_type;

	value_type min;
	value_type max;
};

template<class T>
Pair<T> minMAX(T* array, int start, int end)
{
	Pair<T> solution;

	if ((end - start) < 2) // 0 or 1 element
	{
		if (array[start] < array[end])
		{
			solution.min = array[start];
			solution.max = array[end];
		}
		else
		{
			solution.min = array[end];
			solution.max = array[start];
		}
	}
	else // 2 or more elements
	{
		Pair<T> temp1 = minMAX(array, start, ((end + start) / 2)); // first half
		Pair<T> temp2 = minMAX(array, (((end + start) / 2) + 1), end); // second half

		if (temp1.min < temp2.min)
			solution.min = temp1.min;
		else
			solution.min = temp2.min;

		if (temp1.max > temp2.max)
			solution.max = temp1.max;
		else
			solution.max = temp2.max;
	}

	return solution;
}

#endif // _MINMAX_H
