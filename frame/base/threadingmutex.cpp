#include "threadingmutex.h"

#ifdef WIN32
TMutex::TMutex(){ InitializeCriticalSection(&cs); }
TMutex::~TMutex(){ DeleteCriticalSection(&cs); }
#else
/* this is done slightly differently on bsd-variants */
#if defined(__FreeBSD__) ||  defined(__APPLE_CC__) || defined(__OpenBSD__)
#define recursive_mutex_flag PTHREAD_MUTEX_RECURSIVE
#else
#define recursive_mutex_flag PTHREAD_MUTEX_RECURSIVE_NP
#endif
/* Linux mutex implementation */
bool TMutex::attr_initialized = false;
pthread_mutexattr_t TMutex::attr;

TMutex::TMutex()
{
	if(!attr_initialized)
	{
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr,recursive_mutex_flag);
		attr_initialized = true;
	}
	pthread_mutex_init(&mutex,&attr);
}

TMutex::~TMutex(){pthread_mutex_destroy(&mutex); }

#endif