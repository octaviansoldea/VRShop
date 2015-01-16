#include <string>

#include "BasicStringDefinitions.h"
#include "Singleton.h"
#include "Trace.h"
#include "PipeMgr.h"
#include "PipeNamesMgr.h"

using namespace std;

PipeMgr::PipeMgr() : 
m_bHandleInitialized(false),
m_bSynchronizationInitialized(false)
{
}

PipeMgr::~PipeMgr() {
	if(m_bHandleInitialized) 
		CloseHandle(m_hPipe);
	if(m_bSynchronizationInitialized)
		CloseHandle(m_hSynchronizationEvent); 
}

void PipeMgr::ClosePipeHandle() {
	if(m_bHandleInitialized)
		CloseHandle(m_hPipe);
	m_bHandleInitialized = false;
}

void PipeMgr::initialize(const std::string & astrName, const std::string & astrMediaType, int anID) {
	m_str_Id_MediaType_Name = astrName + itostr(anID) + astrMediaType;
	PipeNamesMgr::computePipeName(m_strPipeName, astrMediaType, anID);
	m_hSynchronizationEvent = CreateEvent(
		                                  NULL,//LPSECURITY_ATTRIBUTES lpEventAttributes,  // SD
										  TRUE,//BOOL bManualReset,                        // reset type
										  FALSE,//BOOL bInitialState,                      // initial state
										  ("Event"+m_str_Id_MediaType_Name).c_str()//LPCTSTR lpName  // object name
                                         );
	m_bSynchronizationInitialized = true;
}

