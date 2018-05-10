#ifndef _PQHEAP_H_
#define _PQHEAP_H_

#include "priority_queue.h"
#include "elempq.h"

// Labels can be duplicated
// Priority can be duplicated
// For numbers: minimum number = max priority; for string: first in alphabetical order = max priority
// Can't change one item's label
// Can't change one item's priority

template<class T, class P>
class Heap: public PriorQueue<Elem<T, P>, int>
{

public:
	typedef typename PriorQueue<Elem<T, P>, int>::elem elem;
	typedef typename PriorQueue<Elem<T, P>, int>::position position;
	typedef T value_type;
	typedef P priority;

	Heap();
	Heap(int); //Size
	Heap(const Heap<T, P>&);
	~Heap();

	Heap<T, P>& operator =(const Heap<T, P>&);
	bool operator == (const Heap<T, P>&);
	bool operator != (const Heap<T, P>&);

	bool empty() const; // true if the tree is empty
	void insert(const elem&); // insert an element in the queue
	void pop(); // delete the first element having highest priority
	elem getMin() const; // return the the first element with the highest priority
	elem getMax() const; // return the the last element with the lowest priority

	void insert(const value_type&, const priority&); // insert an element in the queue
	void epuratePriorities(const priority&); // epurate all the elements having that priority
	void epurateItems(const value_type&); // epurate all the elements having that items

private:
	int MAXLEN;
	elem *heap;
	int freePos; // first empty position of the heap (= # of elements in the heap)

	void create(); // create the queue

	void arrayDoubling(elem*&, const int, const int);
	void fixUp();
	void fixDown(int, int);

};

template<class T, class P>
Heap<T, P>::Heap()
{
	MAXLEN = 100;
	heap = 0;
	freePos = 0;
	this->create();
}

template<class T, class P>
Heap<T, P>::Heap(int size)
{
	if (size <= 0)
		throw std::logic_error("Heap (exception)");

	MAXLEN = size;
	heap = 0;
	freePos = 0;
	this->create();
}

template<class T, class P>
Heap<T, P>::Heap(const Heap<T, P>& queue)
{
	*this = queue;
}

template<class T, class P>
Heap<T, P>::~Heap()
{
	this->clear();
}

template<class T, class P>
Heap<T, P>& Heap<T, P>::operator =(const Heap<T, P>& queue2)
{
	if (&queue2 != this) // avoid auto-assignment
	{
		if (!this->empty())
			this->clear();

		this->MAXLEN = queue2.MAXLEN;
		this->freePos = queue2.freePos;
		this->heap = new elem[MAXLEN];

		for (int i = 0; i < freePos; i++)
			this->heap[i] = queue2.heap[i];
	}

	return *this;
}

template<class T, class P>
bool Heap<T, P>::operator == (const Heap<T, P>& h2)
{
	if (this->freePos != h2.freePos)
		return false;

	for(int i = 0; i < freePos; i++)
		if(this->heap[i] != h2.heap[i])
			return false;

	return true;
}

template<class T, class P>
bool Heap<T, P>::operator != (const Heap<T, P>& h2)
{
	return (!(*this == h2));
}

template<class T, class P>
bool Heap<T, P>::empty() const
{
	return (freePos == 0);
}

template<class T, class P>
void Heap<T, P>::insert(const elem& e)
{
	if (freePos == MAXLEN)
	{
		this->arrayDoubling(heap, MAXLEN, MAXLEN * 2);
		MAXLEN = MAXLEN * 2;
	}

	heap[freePos] = e;
	freePos++;
	this->fixUp();
}

template<class T, class P>
void Heap<T, P>::insert(const value_type& val, const priority& pri)
{
	if (freePos == MAXLEN)
	{
		this->arrayDoubling(heap, MAXLEN, MAXLEN * 2);
		MAXLEN = MAXLEN * 2;
	}

	(heap[freePos]).setValue(val);
	(heap[freePos]).setPriority(pri);
	freePos++;
	this->fixUp();
}

template<class T, class P>
void Heap<T, P>::pop()
{
	if (this->empty())
		throw std::logic_error("Heap (exception)");

	heap[0] = heap[freePos - 1];
	freePos--;
	this->fixDown(1, freePos);
}

template<class T, class P>
typename Heap<T, P>::elem Heap<T, P>::getMin() const
{
	if (this->empty())
		throw std::logic_error("Heap (exception)");

	return heap[0];
}

template<class T, class P>
typename Heap<T, P>::elem Heap<T, P>::getMax() const
{
	if (this->empty())
		throw std::logic_error("Heap (exception)");

	return heap[freePos - 1];
}

template<class T, class P>
void Heap<T, P>::create()
{
	heap = new elem[MAXLEN];
}

template<class T, class P>
void Heap<T, P>::arrayDoubling(elem*& a, const int oldSize, const int newSize)
{
	elem* temp = new elem[newSize];

	for (int i = 0; i < oldSize; i++)
		temp[i] = a[i];

	delete[] a;
	a = temp;
}

template<class T, class P>
void Heap<T, P>::fixUp()
{
	int k = freePos;

	while (k > 1 && heap[k - 1] < heap[k / 2 - 1])
	{
		elem tmp = elem();
		tmp = heap[k - 1];
		heap[k - 1] = heap[k / 2 - 1];
		heap[k / 2 - 1] = tmp;
		k = k / 2;
	}
}

template<class T, class P>
void Heap<T, P>::fixDown(int k, int N)
{
	short int scambio = 1;

	while (k <= N / 2 && scambio)
	{
		int j = 2 * k;
		elem tmp = elem();
		if (j < N && heap[j - 1] > heap[j])
			j++;
		if ((scambio = heap[j - 1] < heap[k - 1]))
		{
			tmp = heap[k - 1];
			heap[k - 1] = heap[j - 1];
			heap[j - 1] = tmp;
			k = j;
		}
	}
}

template<class T, class P>
void Heap<T, P>::epuratePriorities(const priority& p)
{
	vector<elem> elements;

	//Copy the first queue
	while (!this->empty())
	{
		if ( (this->getMin()).getPriority() != p)
			elements.push_back(this->getMin());
		this->pop();
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}
}

template<class T, class P>
void Heap<T, P>::epurateItems(const value_type& i)
{
	vector<elem> elements;

	//Copy the first queue
	while (!this->empty())
	{
		if ( (this->getMin()).getValue() != i)
			elements.push_back(this->getMin());
		this->pop();
	}

	while (!elements.empty())
	{
		this->insert(elements.back());
		elements.pop_back();
	}
}

#endif /* _PQHEAP_H_ */
