#ifndef CHRONOMTER_REAL_TIME_H 
#define CHRONOMTER_REAL_TIME_H

#include <windows.h>

#include "Chronometer.h"

class Chronometer_RealTime : public Chronometer {
	DWORD m_RefTime;
public:

	Chronometer_RealTime();

	virtual void Start();
	virtual void Stop();
};

#endif //CHRONOMTER_REAL_TIME_H