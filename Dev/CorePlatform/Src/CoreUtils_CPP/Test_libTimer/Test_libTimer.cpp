#include <Windows.h>
#include <stdio.h>

#include "Timer.h"
#include "Chronometer.h"

int main() {

	Timer * pCPUTime, * pRealTime, * pQueryPerformanceTime;

	pCPUTime = Timer::CreateInstance(TimerBase::CLOCK);
	pRealTime = Timer::CreateInstance(TimerBase::REAL_TIME);
	pQueryPerformanceTime = Timer::CreateInstance(TimerBase::QUERY_PERFPORMANCE);

	int nI;

	for(nI = 0; nI < 10; nI++) {
		printf("-----------------------------\n");
		int nCPUTime = pCPUTime->getCurrTimeInMiliSeconds();
		int nRealTime = pRealTime->getCurrTimeInMiliSeconds();
		int nQueryPerformanceTime = pQueryPerformanceTime->getCurrTimeInMiliSeconds();
		printf("CPU time = %d - Real time = %d - Query performance time = %d\n", nCPUTime, nRealTime, nQueryPerformanceTime);

		double dbCPUTime = pCPUTime->getCurrTimeInSeconds();
		double dbRealTime = pRealTime->getCurrTimeInSeconds();
		double dbQueryPerformanceTime = pQueryPerformanceTime->getCurrTimeInSeconds();
		printf("CPU time = %f - Real time = %f - Query performance = %f\n", dbCPUTime, dbRealTime, dbQueryPerformanceTime);

		int ii = 1;
		for(int nJ = 0; nJ < 10; nJ++) {
			ii += nJ * nI;
		}
		printf("stam ii = %d\n", ii);

		Sleep(1000);
	}

	delete pCPUTime;
	delete pRealTime;
	delete pQueryPerformanceTime;

	int nMSElapsedTime;
	double dbElabsedTime;

	{
		Chronometer * pChCPU = Chronometer::CreateInstance(TimerBase::CLOCK);	
		pChCPU->init();


		pChCPU->Start();
		pChCPU->Stop();
		nMSElapsedTime = pChCPU->getAccTimeInMiliSeconds();
		dbElabsedTime = pChCPU->getAccTimeInSeconds();

		pChCPU->Start();
		pChCPU->Stop();
		nMSElapsedTime = pChCPU->getAccTimeInMiliSeconds();
		dbElabsedTime = pChCPU->getAccTimeInSeconds();

	}
	{
		Chronometer * pChRealTime = Chronometer::CreateInstance(TimerBase::REAL_TIME);
		pChRealTime->init();

		pChRealTime->Start();
		pChRealTime->Stop();
		nMSElapsedTime = pChRealTime->getAccTimeInMiliSeconds();
		dbElabsedTime = pChRealTime->getAccTimeInSeconds();
		
		pChRealTime->Start();
		pChRealTime->Stop();
		nMSElapsedTime = pChRealTime->getAccTimeInMiliSeconds();
		dbElabsedTime = pChRealTime->getAccTimeInSeconds();

	}

	{
		Chronometer * pChQueryPerformanceTime = Chronometer::CreateInstance(TimerBase::QUERY_PERFPORMANCE);
		pChQueryPerformanceTime->init();

		pChQueryPerformanceTime->Start();
		pChQueryPerformanceTime->Stop();
		nMSElapsedTime = pChQueryPerformanceTime->getAccTimeInMiliSeconds();
		dbElabsedTime = pChQueryPerformanceTime->getAccTimeInSeconds();
		
		pChQueryPerformanceTime->Start();
		pChQueryPerformanceTime->Stop();
		nMSElapsedTime = pChQueryPerformanceTime->getAccTimeInMiliSeconds();
		dbElabsedTime = pChQueryPerformanceTime->getAccTimeInSeconds();

	}


	return(0);
}