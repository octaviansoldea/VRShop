#include <iostream>

#include "Timer.h"
#include "Timer_CPUTime.h"
#include "Timer_RealTime.h"
#include "Timer_QueryPerformance.h"

using namespace std;

Timer::Timer() {
}

Timer::~Timer() {
}

Timer * Timer::CreateInstance(TYPE_TIMER a_type_tymer) {

	Timer * pTimer = NULL;
	switch(a_type_tymer) {
		case REAL_TIME :
			pTimer = new Timer_RealTime();
			break;
		case CLOCK :
			pTimer = new Timer_CPUTime();
			break;
		case QUERY_PERFPORMANCE :
			pTimer = new Timer_QueryPerformance();
			break;
		default :
			cerr << "Warning: Could not determine the type of timer to create" << endl;
			break;
	}
	return(pTimer);

}

unsigned long double Timer::getCurrTimeInSeconds() const {
	unsigned long double udbDuration = (unsigned long double) (((double)getCurrTimeInMiliSeconds()) / ((double)CLOCKS_PER_SEC));
	return(udbDuration);
}

