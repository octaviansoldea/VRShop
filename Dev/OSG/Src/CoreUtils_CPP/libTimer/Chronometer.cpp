#include <iostream>

#include "Chronometer.h"
#include "Chronometer_CPUTime.h"
#include "Chronometer_RealTime.h"
#include "Chronometer_QueryPerformance.h"

using namespace std;

Chronometer::Chronometer() : m_bIsRunnning(false), m_unll_MS_AccTime(0) {
}

void Chronometer::init() {
	m_bIsRunnning = false;
	m_unll_MS_AccTime = 0;
}

void Chronometer::Start() {
	if(m_bIsRunnning == true) {
		cerr << "Uncorrect time measurements detected " << endl;
		exit(-1);
	}
	m_bIsRunnning = true;
}

void Chronometer::Stop() {
	if(m_bIsRunnning == false) {
		cerr << "Uncorrect time measurements detected " << endl;
		exit(-1);
	}
	m_bIsRunnning = false;
}

Chronometer * Chronometer::CreateInstance(TYPE_TIMER a_type_tymer) {

	Chronometer * pChronometer = NULL;
	switch(a_type_tymer) {
		case REAL_TIME :
			pChronometer = new Chronometer_RealTime();
			break;
		case CLOCK :
			pChronometer = new Chronometer_CPUTime();
			break;
		case QUERY_PERFPORMANCE :
			pChronometer = new Chronometer_QueryPerformance();
			break;
	}
		
	return(pChronometer);

}

unsigned long double Chronometer::getAccTimeInSeconds() const {
	unsigned long double udbDuration = (unsigned long double) (((double)getAccTimeInMiliSeconds()) / ((double)CLOCKS_PER_SEC));
	return(udbDuration);
}

unsigned long long Chronometer::getAccTimeInMiliSeconds() const {
	if(m_bIsRunnning == true) {
		cerr << "Trial to require time when Chronometer was running" << endl;
		exit(-1);
	}
	return(m_unll_MS_AccTime);
}