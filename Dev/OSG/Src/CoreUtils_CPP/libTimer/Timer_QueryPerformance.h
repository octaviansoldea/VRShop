#ifndef TIMER_QUERY_PERFORMANCE_H
#define TIMER_QUERY_PERFORMANCE_H

#include <Windows.h>

#include "Timer.h"

class Timer_QueryPerformance : public Timer {
	LARGE_INTEGER m_nFrequency;
	LARGE_INTEGER m_nRefCount;
public:
	Timer_QueryPerformance();

	virtual void init();
	virtual unsigned long long getCurrTimeInMiliSeconds() const;
};

#endif //TIMER_QUERY_PERFORMANCE_H