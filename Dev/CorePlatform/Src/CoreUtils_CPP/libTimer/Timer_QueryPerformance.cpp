#include <iostream>
#include <time.h>

#include "Timer_QueryPerformance.h"

using namespace std;

Timer_QueryPerformance::Timer_QueryPerformance() { 
	BOOL bOk = QueryPerformanceFrequency(&m_nFrequency);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceFrequency" << endl;
		exit(-1);
	}
	bOk = QueryPerformanceCounter(&m_nRefCount);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceCounter" << endl;
		exit(-1);
	}
}

void Timer_QueryPerformance::init() {
	BOOL bOk = QueryPerformanceCounter(&m_nRefCount);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceCounter" << endl;
		exit(-1);
	}
}


unsigned long long Timer_QueryPerformance::getCurrTimeInMiliSeconds() const {
	LARGE_INTEGER nCurrCount;
	BOOL bOk = QueryPerformanceCounter(&nCurrCount);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceCounter" << endl;
		exit(-1);
	}
	double dbDiff = (double)(nCurrCount.QuadPart - m_nRefCount.QuadPart);
	dbDiff /= ((double)(m_nFrequency.QuadPart));
	dbDiff *= 1000.0;
	unsigned long long unMiliSeconds = (unsigned long long)dbDiff;
	return(unMiliSeconds);
}