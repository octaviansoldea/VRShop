#ifndef TIMER_BASE_H
#define TIMER_BASE_H

class TimerBase {
public:
	typedef enum {REAL_TIME, CLOCK, QUERY_PERFPORMANCE} TYPE_TIMER;

	virtual void init() = 0;
};

#endif //TIMER_BASE_H