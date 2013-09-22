#ifndef TIMER_REAL_TIME_H
#define TIMER_REAL_TIME_H

#include <windows.h>

#include "Timer.h"

class Timer_RealTime : public Timer {
	DWORD m_RefTime;
public:
	Timer_RealTime();
	//virtual ~Timer_RealTime();
	virtual void init();
	virtual unsigned long long getCurrTimeInMiliSeconds() const;
};

#endif //TIMER_REAL_TIME_H