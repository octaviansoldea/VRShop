#include "PipeMgrAutoDeblocking.h"
#include "BasicStringDefinitions.h"

#include <string>

#include "Singleton.h"
#include "Trace.h"
#include "PipeMgr.h"

using namespace std;

PipeMgrAutoDeblocking::PipeMgrAutoDeblocking() :
m_bMutexInitialized(false)
{

	/*m_hSynchronizationEvent = CreateEvent(
		                                  NULL,//LPSECURITY_ATTRIBUTES lpEventAttributes,  // SD
										  TRUE,//BOOL bManualReset,                        // reset type
										  FALSE,//BOOL bInitialState,                      // initial state
										  ("Event"+m_strGenericName).c_str()//LPCTSTR lpName  // object name
                                         );

	*/
	
}

PipeMgrAutoDeblocking::~PipeMgrAutoDeblocking() {
	if(m_bMutexInitialized) {
		CloseHandle(m_Mutex);
	} 
}

void PipeMgrAutoDeblocking::initialize(const std::string & astrName, const std::string & astrMediaType, int anID) {
	PipeMgr::initialize(astrName, astrMediaType, anID);
	
	string strMutexName = "Mutex"+m_str_Id_MediaType_Name;
#ifdef DEBUG_PRINT
	printf(strMutexName.c_str());
#endif DEBUG_PRINT

#if UNICODE
	LPCTSTR lpMutexName = string2WString(strMutexName).c_str();
#else
	LPCTSTR lpMutexName = strMutexName.c_str();
#endif	

	m_Mutex = CreateMutex(NULL, FALSE, lpMutexName);
	m_bMutexInitialized = true;
}
