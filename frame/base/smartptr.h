#include "mutex.h"

template<class T>
class SharedPtr
{
public:
	explicit SharedPtr(T *p):m_ptr(p),m_count(1){}
	~SharedPtr()
	{

	}
	SharedPtr(SharedPtr& sp):m_ptr(sp.m_ptr),m_count(sp.m_count) /// 不需要复制索
	{
		AddRef();
	}

	SharedPtr operator=(SharedPtr& sp)
	{
		sp.AddRef();
		DecRef();
		m_ptr = sp.m_ptr;
		m_count = sp.m_count;
		return *this;
	}

	T& operator*(){return *m_ptr;}
	T* operator->(){return m_ptr;}

private:
	T* m_ptr;
	int m_count;
	Mutex m_count_mutex;
private:
	void AddRef()
	{
		m_count_mutex.Lock();
		++m_count;
		m_count_mutex.UnLock();
	}
	void DecRef()
	{
		m_count_mutex.Lock();
		if(0 == --m_count)
		{
			delete m_ptr;
			m_ptr = NULL;
		}
		m_count_mutex.UnLock();
	}
};

