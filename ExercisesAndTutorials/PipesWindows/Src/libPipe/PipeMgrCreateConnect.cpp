#include <string>
#include "BasicStringDefinitions.h"

#include "Singleton.h"
#include "Trace.h"
#include "PipeMgrCreateConnect.h"

using namespace std;

bool PipeMgrCreateConnect::createPipe(DWORD adwOpenMode) {
	if(m_bHandleInitialized) {
		printf("Error: Reinitialization of a handle that was already set");
		return(false);
	}

	if((adwOpenMode != PIPE_ACCESS_INBOUND) && (adwOpenMode != PIPE_ACCESS_OUTBOUND)) {
		Singleton<Trace>::instance()->printWarningMessage("Problems in open mode specifications\n");
		return(false);
	}

	m_dwMode = adwOpenMode;
	//m_strPipeName = apchPipeName;

#if UNICODE
	LPCTSTR lpName = string2WString(m_strPipeName).c_str();
#else
	LPCTSTR lpName = m_strPipeName.c_str();
#endif	
	m_hPipe = CreateNamedPipe(
                              lpName,                   // pipe name
                              //PIPE_ACCESS_OUTBOUND,     // pipe open mode
							  adwOpenMode,
							  PIPE_TYPE_MESSAGE|PIPE_WAIT, // pipe-specific modes
							  1,                        // maximum number of instances
							  0,                        // output buffer size
							  0,                        // input buffer size
							  INFINITE,                 // time-out interval
							  NULL                      // SD
							 );
	if(m_hPipe == NULL){
		printf("Error: Cannot create named pipe %s\n", lpName);
		return(false);
	}
	m_bHandleInitialized = true;
	return(true);
}

bool PipeMgrCreateConnect::connectPipe() {
	if((m_bHandleInitialized == false) || (m_bSynchronizationInitialized == false))
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrCreateConnect::connectPipe problems with pipe initialization");

	BOOL bRes = ConnectNamedPipe(m_hPipe, NULL);
	if(bRes == FALSE){
		string strWarningMsg("PipeMgrCreateConnect::connectPipe Cannot connect named pipe ");
		strWarningMsg += m_strPipeName;
		Singleton<Trace>::instance()->printWarningMessage(strWarningMsg.c_str());

		return(false);
	}
	return(true);
}

bool PipeMgrCreateConnect::createAndConnect(DWORD adwOpenMode) {
	bool bOk = createPipe(adwOpenMode);

	if((m_bHandleInitialized == false) || (m_bSynchronizationInitialized == false))
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrCreateConnect::createAndConnect problems with pipe initialization");

	if(bOk) {
		SetEvent(m_hSynchronizationEvent);
	} else {
		Singleton<Trace>::instance()->printWarningMessage("Cannot create pipe");
		return(false);
	}
	bOk = bOk && connectPipe();
	return(bOk);
}
