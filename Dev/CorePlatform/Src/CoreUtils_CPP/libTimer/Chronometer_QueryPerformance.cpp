#include <iostream>

#include "Chronometer_QueryPerformance.h"

using namespace std;

Chronometer_QueryPerformance::Chronometer_QueryPerformance() { 
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

void Chronometer_QueryPerformance::Start() {
	Chronometer::Start();
	BOOL bOk = QueryPerformanceCounter(&m_nRefCount);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceCounter" << endl;
		exit(-1);
	}
}

void Chronometer_QueryPerformance::Stop() {
	Chronometer::Stop();
	LARGE_INTEGER nCurrCount;
	BOOL bOk = QueryPerformanceCounter(&nCurrCount);
	if(bOk == false) {
		cerr << "Error: could not execute QueryPerformanceCounter" << endl;
		exit(-1);
	}
	double dbDiff = (double)(nCurrCount.QuadPart - m_nRefCount.QuadPart);
	dbDiff /=  ((double)(m_nFrequency.QuadPart));
	dbDiff *= 1000.0;
	unsigned long long unMiliSeconds = (unsigned long long)dbDiff;
	m_unll_MS_AccTime += unMiliSeconds;
}