#include <time.h>

#include "Chronometer.h"
#include "Chronometer_CPUTime.h"

Chronometer_CPUTime::Chronometer_CPUTime() { 
	m_RefTime = clock();
}

void Chronometer_CPUTime::Start() {
	Chronometer::Start();
	m_RefTime = clock();
}

void Chronometer_CPUTime::Stop() {
	Chronometer::Stop();
	clock_t currTime = clock();
	unsigned long long unMiliSeconds = (unsigned long long) (currTime - m_RefTime);
	m_unll_MS_AccTime += unMiliSeconds;
}