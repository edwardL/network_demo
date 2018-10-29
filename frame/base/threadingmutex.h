#ifndef _THREADING_MUTEX_H
#define _THREADING_MUTEX_H
#include<Windows.h>
#include <pthread.h>

class TMutex
{
public:
	/** Initializes a mutex class, with InitializeCriticalSection / pthread_mutex_init
	 */
	 TMutex();
	/** Deletes the associated critical section / mutex
	 */
	~TMutex();

	void Acquire()
	{
#ifndef WIN32
		pthread_mutex_lock(&mutex);
#else
		EnterCriticalSection(&cs);
#endif
	}

	void Release()
	{
#ifndef WIN32
		pthread_mutex_unlock(&mutex);
#else
		LeaveCriticalSection(&cs);
#endif
	}

	bool AttemptAcquire()
	{
#ifndef WIN32
		return (pthread_mutex_trylock(&mutex) == 0);
#else
		return (TryEnterCriticalSection(&cs) == TRUE);
#endif
	}

protected:
#ifdef WIN32
	CRITICAL_SECTION cs;
#else
	static bool attr_initialized;
	static pthread_mutexattr_t attr;

	pthread_mutex_t mutex;
#endif
	
};



#endif