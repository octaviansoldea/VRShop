#include <string>

#include "BasicStringDefinitions.h"
#include "Singleton.h"
#include "Trace.h"

#include "PipeMgrAutoDeblockingWriteInterface.h"

using namespace std;

bool PipeMgrAutoDeblockingWriteInterface::createPipe() {
	string strError = "PipeMgrAutoDeblockingWriteInterface::createPipe + ";
	if(m_bHandleInitialized) {
		strError += "problems with mutex initialization";
		Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
		//printf("Error: Reinitialization of a handle that was already set");
		return(false);
	}

	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrAutoDeblockingWriteInterface::createPipe problems with mutex initialization");

	LPCTSTR lpName = m_strPipeName.c_str();
	m_hPipe = CreateNamedPipe(
                              lpName,                   // pipe name
                              //PIPE_ACCESS_OUTBOUND,     // pipe open mode
							  PIPE_ACCESS_OUTBOUND,
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

bool PipeMgrAutoDeblockingWriteInterface::connectPipe() {
	string strErr = "PipeMgrAutoDeblockingWriteInterface::connectPipe - ";
	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage((strErr + "problems with mutex initialization").c_str());

	BOOL bOk = ConnectNamedPipe(m_hPipe, NULL);
	DWORD dwErr = GetLastError();
	if((bOk == TRUE) ||
		((bOk == FALSE) && (dwErr == ERROR_PIPE_CONNECTED))) {
		return(true);
	} else {
		Singleton<Trace>::instance()->printWarningMessage((strErr + "Error: Cannot connect named pipe" + m_strPipeName).c_str());
		Singleton<Trace>::instance()->printWarningMessage((string("The error code detected was:") + itostr(dwErr)).c_str());
		//Unkown bug!!!!!
		//return(false);
	}
	return(true);
}

bool PipeMgrAutoDeblockingWriteInterface::createAndConnectAndTransmitPIDAndHandle() {
	string strError = "PipeMgrAutoDeblockingWriteInterface::createAndConnectAndTransmitPIDAndHandle - ";
	DWORD dwErr;

	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage((strError + " problems with mutex initialization").c_str());

	bool bOk = createPipe();
	if(bOk) {
		SetEvent(m_hSynchronizationEvent);
	} else {
		Singleton<Trace>::instance()->printWarningMessage((strError + "Cannot create pipe").c_str());
		dwErr = GetLastError();
		//printf("The error code detected was: %d\n", dwErr);
		return(false);
	}

	bOk = connectPipe();
	if(bOk == false) {
		Singleton<Trace>::instance()->printWarningMessage((strError + "Cannot connect pipe").c_str());
		dwErr = GetLastError();
		//printf("The error code detected was: %d\n", dwErr);
		return(false);
	}
	
	PIDAndHandle pidAndHandle;
	pidAndHandle.m_PID = GetCurrentProcessId();
	pidAndHandle.m_HANDLE = m_hPipe;
	DWORD nNumberOfBytesWritten;
	BOOL bOkWin = WriteFile(m_hPipe, &pidAndHandle, sizeof(PIDAndHandle), &nNumberOfBytesWritten, NULL);
	if(bOkWin == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage((strError + "Cannot write PID and Handle").c_str());
		dwErr = GetLastError();
		//printf("The error code detected was: %d\n", dwErr);
		return(false);
	}

	return(true);
}

bool PipeMgrAutoDeblockingWriteInterface::write(const unsigned char * apuchMessage, int anLength) {
	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrAutoDeblockingWriteInterface::write problems with mutex initialization");

	WaitForSingleObject(m_Mutex, INFINITE);

	DWORD nNumberOfBytesWritten = 0;
	BOOL bOk1 = WriteFile(m_hPipe, &anLength, sizeof(int), &nNumberOfBytesWritten, NULL);
	BOOL bOk2 = bOk1 && WriteFile(m_hPipe, apuchMessage, anLength, &nNumberOfBytesWritten, NULL);
	if(!bOk2) {
		DWORD dwErr = GetLastError();
		Singleton<Trace>::instance()->printWarningMessage("Cannnot write to named pipe");
		//printf("The error code detected was: %d\n", dwErr);
	}

	ReleaseMutex(m_Mutex);

	return(!!bOk2);
	
}