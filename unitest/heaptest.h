#include "../frame/base/heap.h"
#include "../frame/file/singlemanager.h"

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

class SingleManagerTest
{
public:
	SingleManagerTest()
	{
		SingleManager m_single_manager;
		m_single_manager.Init();
		int* a = new int(1);
		int* b = new int(2);
		m_single_manager.Add(a);
		m_single_manager.Add(b);
		m_single_manager.Remove(a);
		m_single_manager.Remove(b);
	}
};