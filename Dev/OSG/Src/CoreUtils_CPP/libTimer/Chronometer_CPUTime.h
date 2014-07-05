#ifndef CHRONOMETER_CPU_TIME_H
#define CHRONOMETER_CPU_TIME_H

#include <time.h>

#include "Chronometer.h"

class Chronometer_CPUTime : public Chronometer {
	clock_t m_RefTime;

public:	
	
	Chronometer_CPUTime();

	virtual void Start();
	virtual void Stop();
};

#endif //CHRONOMETER_CPU_TIME_H