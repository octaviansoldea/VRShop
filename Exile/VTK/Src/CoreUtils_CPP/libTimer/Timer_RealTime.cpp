#include "Timer.h"
#include "Timer_RealTime.h"

Timer_RealTime::Timer_RealTime() {
	m_RefTime = timeGetTime();
}

//Timer_RealTime::~Timer_RealTime() {}

void Timer_RealTime::init() {
	m_RefTime = timeGetTime();
}

unsigned long long Timer_RealTime::getCurrTimeInMiliSeconds() const {
	DWORD currTime = timeGetTime();
	unsigned long long unMiliSeconds = (unsigned long long) (currTime - m_RefTime);
	return(unMiliSeconds);
}