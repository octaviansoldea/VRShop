#include <time.h>

#include "Timer.h"
#include "Timer_CPUTime.h"


Timer_CPUTime::Timer_CPUTime() { 
	m_RefTime = clock(); 
}

void Timer_CPUTime::init() { 
	m_RefTime = clock(); 
}


unsigned long long Timer_CPUTime::getCurrTimeInMiliSeconds() const {
	clock_t currTime = clock();
	unsigned long long unMiliSeconds = (unsigned long long) (currTime - m_RefTime);
	return(unMiliSeconds);
}