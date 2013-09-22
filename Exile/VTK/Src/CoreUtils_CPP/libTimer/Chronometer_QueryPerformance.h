#ifndef CHRONOMETER_QUERY_PERFORMANCE_H
#define CHRONOMETER_QUERY_PERFORMANCE_H

#include <Windows.h>

#include "Chronometer.h"

class Chronometer_QueryPerformance : public Chronometer {
	LARGE_INTEGER m_nFrequency;
	LARGE_INTEGER m_nRefCount;
public:	
	
	Chronometer_QueryPerformance();

	virtual void Start();
	virtual void Stop();
};

#endif //CHRONOMETER_QUERY_PERFORMANCE_H