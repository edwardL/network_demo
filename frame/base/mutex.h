#ifndef MUTEX_H
#define MUTEX_H
#include <pthread.h>

class Mutex
{
public:
	Mutex();
	~Mutex();
	void Lock();
	void UnLock();
	void Destroy();

private:
	pthread_mutex_t _lock;
	bool m_destroyed;

	Mutex(const Mutex&){}
	Mutex& operator=(const Mutex &){}
};

class Mutex1
{
public:
	Mutex1()
	{
		pthread_mutex_init(&_lock,NULL);
	}
	~Mutex1()
	{
		Destroy();
	}
	void Lock()
	{
		pthread_mutex_lock(&_lock);
	}
	void UnLock()
	{
		pthread_mutex_unlock(&_lock);
	}
	void Destroy()
	{
		pthread_mutex_destroy(&_lock);
	}

private:
	pthread_mutex_t _lock;
	Mutex1(const Mutex1&){}
	Mutex1& operator=(const Mutex1&){}
};




class Mutex2
{
public:
	Mutex2();
	~Mutex2();

private:
	pthread_mutex_t _lock;
	Mutex2(const Mutex2&){}
	Mutex2& operator=(const Mutex2 &){}
};


#endif