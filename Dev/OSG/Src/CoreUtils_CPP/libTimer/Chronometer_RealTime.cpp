#include "Chronometer.h"
#include "Chronometer_RealTime.h"

Chronometer_RealTime::Chronometer_RealTime() {
	m_RefTime = timeGetTime();
}

void Chronometer_RealTime::Start() {
	Chronometer::Start();
	m_RefTime = timeGetTime();
}

void Chronometer_RealTime::Stop() {
	Chronometer::Stop();
	DWORD currTime = timeGetTime();
	unsigned long long unMiliSeconds = (unsigned long long) (currTime - m_RefTime);
	m_unll_MS_AccTime += unMiliSeconds;
}