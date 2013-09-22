#ifndef TIMER_CPU_TIME_H
#define TIMER_CPU_TIME_H

#include <time.h>

#include "Timer.h"

class Timer_CPUTime : public Timer {
	clock_t m_RefTime;
public:
	Timer_CPUTime();

	virtual void init();
	virtual unsigned long long getCurrTimeInMiliSeconds() const;
};

#endif //TIMER_CPU_TIME_H