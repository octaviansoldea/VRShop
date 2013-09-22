#ifndef CHRONOMTER_H
#define CHRONOMTER_H

#include "TimerBase.h"

class Chronometer : public TimerBase {
protected:
	Chronometer();

	bool m_bIsRunnning;
	unsigned long long m_unll_MS_AccTime;
public:

	static Chronometer * CreateInstance(TYPE_TIMER a_type_tymer = REAL_TIME);

	virtual void Start() = 0;
	virtual void Stop() = 0;

	virtual void init();
	unsigned long double getAccTimeInSeconds() const;
	unsigned long long getAccTimeInMiliSeconds() const;
};

#endif //CHRONOMTER_H