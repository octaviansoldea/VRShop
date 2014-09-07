#ifndef TIMER_H
#define TIMER_H

#include "TimerBase.h"

class Timer : public TimerBase {

protected:
	Timer();
public:

	static Timer * CreateInstance(TYPE_TIMER a_type_tymer = REAL_TIME);
	virtual ~Timer() = 0;

	virtual void init() = 0;
	unsigned long double getCurrTimeInSeconds() const;
	virtual unsigned long long getCurrTimeInMiliSeconds() const = 0;
};

#endif //TIMER_H