#include "basetool.h"

void MS_SLEEP(int time)
{
	#ifdef WIN32
		Sleep(time);
	#else
		usleep(t* 1000);
	#endif
}