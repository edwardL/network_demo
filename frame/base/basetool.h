#ifndef BASE_TOOL_H
#define BASE_TOOL_H

#ifdef WIN32
	#include<Windows.h>
#else
	#include<unistd.h>
#endif

void MS_SLEEP(int time);

#endif