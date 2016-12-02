#ifndef TIMER_H
#define TIMER_H

#ifdef WIN32
#include <Windows.h>


#include <time.h>
typedef long clock_t;

class Timer
{
private:
	clock_t mZeroClock;
	DWORD mStartTick;
	LONGLONG mLastTime;
	LARGE_INTEGER mStartTime;
	LARGE_INTEGER mFrequency;

	DWORD_PTR mTimerMask;

private:
	Timer();
	~Timer();
	void reset();

public:
	/** return millliseconds since initialisation or last reset */
	// ∑µªÿŒ¢√Î
	static Timer* getInstance();

	unsigned long getMilliseconds();
	// 
	unsigned long getMicroseconds();
};
#else
#include <time.h>
class Timer
{
private:
	struct timeval start;
	clock_t zeroClock;
public:
	Timer();
	~Timer();

	/** Resets timer */
	void reset();

	/** Returns milliseconds since initialisation or last reset */
	unsigned long getMilliseconds();

	/** Returns microseconds since initialisation or last reset */
	unsigned long getMicroseconds();

};

#endif

#endif