#include "../frame/base/heap.h"

class HeapTest
{
public:
	HeapTest()
	{
		Heap<int> h;
		h.Push(12);
		h.Push(1);
		h.Push(13);
		h.Push(2);
		h.PrintHeap();
	}
};