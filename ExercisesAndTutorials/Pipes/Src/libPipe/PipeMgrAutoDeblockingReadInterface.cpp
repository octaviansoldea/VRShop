#include <string>

#include "BasicStringDefinitions.h"
#include "Singleton.h"
#include "Trace.h"
#include "PipeMgrAutoDeblockingReadInterface.h"

using namespace std;

bool PipeMgrAutoDeblockingReadInterface::openPipeAndReadPIDAndHandle() {
	string strError = "PipeMgrAutoDeblockingReadInterface::openPipeAndReadPIDAndHandle - ";
	DWORD dwErr;

	if(m_bHandleInitialized) {
		Singleton<Trace>::instance()->printWarningMessage((strError + "Reinitialization of a handle that was already set").c_str());
		return(false);
	}
	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage((strError + "Problems with mutex initialization").c_str());
	

	LPCTSTR lpName = m_strPipeName.c_str();
	
	WaitForSingleObject(m_hSynchronizationEvent, INFINITE);

	m_hPipe = CreateFile(
	                     lpName,                       // file name
	     				 //GENERIC_READ,               // access mode
						 GENERIC_READ,
						 0,                            // share mode
						 NULL,                         // SD
						 OPEN_EXISTING,                // how to create
						 FILE_ATTRIBUTE_NORMAL,        // file attributes
						 NULL                          // handle to template file
						);
	if(m_hPipe == INVALID_HANDLE_VALUE) {
		dwErr = GetLastError();
		strError += "Error: Cannot open (file - second handle) named " + string(lpName) + "\n";
		Singleton<Trace>::instance()->printWarningMessage(strError.c_str());
		printf("The error code detected was: %d\n", dwErr);
		return(false);
	} else {
	}
	m_bHandleInitialized = true;


	DWORD nNumberOfBytesRead;
	BOOL bOk = ReadFile(m_hPipe, &m_PIDAndHandle, sizeof(m_PIDAndHandle), &nNumberOfBytesRead, NULL);

	//printf("sizeof(m_PIDAndHandle) = %d\n", sizeof(m_PIDAndHandle));
	//printf("nNumberOfBytesRead = %d\n", nNumberOfBytesRead);


	if(bOk == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage((strError + "cannot read PID").c_str());
		dwErr = GetLastError();
		printf("The error code detected was: %d\n", dwErr);
		return(!!bOk);
	} 

	HANDLE hProccessSender = OpenProcess(
										 PROCESS_DUP_HANDLE,//DWORD dwDesiredAccess,  // access flag
										 FALSE,//BOOL bInheritHandle,    // handle inheritance option
										 m_PIDAndHandle.m_PID//DWORD dwProcessId       // process identifier
										);
	bOk = hProccessSender != NULL;
	if(bOk == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage((strError + "cannot open process").c_str());
		dwErr = GetLastError();
		//printf("The error code detected was: %d\n", dwErr);
		return(!!bOk);
	}

	bOk = bOk && DuplicateHandle(
								 hProccessSender,//HANDLE hSourceProcessHandle,  // handle to source process
								 m_PIDAndHandle.m_HANDLE,//HANDLE hSourceHandle,         // handle to duplicate
								 GetCurrentProcess(),//HANDLE hTargetProcessHandle,  // handle to target process
								 &m_hTerminatorPipe,//LPHANDLE lpTargetHandle,      // duplicate handle
								 0,//DWORD dwDesiredAccess,        // requested access
								 FALSE,//BOOL bInheritHandle,          // handle inheritance option
								 DUPLICATE_SAME_ACCESS//DWORD dwOptions               // optional actions
								);
	
	CloseHandle(hProccessSender);
	if(bOk == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage("Cannot duplicate handler");
		dwErr = GetLastError();
		//printf("The error code detected was: %d\n", dwErr);
		return(!!bOk);
	}
	return(!!bOk);
}

bool PipeMgrAutoDeblockingReadInterface::read(string & astrMessage) {

	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrAutoDeblockingReadInterface::read problems with mutex initialization");
	

	DWORD nNumberOfBytesRead;

	unsigned int nSizeOfInt = sizeof(int);

	BOOL bOk = FALSE;

	unsigned int nLength;

	bOk = ReadFile(m_hPipe, &nLength, sizeof(int), &nNumberOfBytesRead, NULL);
	if(bOk == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage("Problems in reading from pipe");
		return(false);
	}

	if(nNumberOfBytesRead == 0)
		return(false);

	if(nLength == 0) {
		astrMessage = "";
		return(true);
	} else {
		unsigned char * puchCurrRead = new unsigned char[nLength + 1];
		if(puchCurrRead == NULL) {
			Singleton<Trace>::instance()->printWarningMessage("Problems in allocating bufer to read into");
			return(false);
		}

		bOk = bOk && ReadFile(m_hPipe, puchCurrRead, nLength, &nNumberOfBytesRead, NULL);
		if(bOk == FALSE) {
			delete [] puchCurrRead;
			Singleton<Trace>::instance()->printWarningMessage("Problems in reading from pipe");
			return(false);
		}
		astrMessage = string((char *)puchCurrRead);

		delete [] puchCurrRead;
	}
	return(true);

}

void PipeMgrAutoDeblockingReadInterface::autoDeblock() {
	if(!m_bMutexInitialized)
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrAutoDeblockingReadInterface::autoDeblock problems with mutex initialization");
	
	DWORD nNumberOfBytesWritten;

	int nVal = 0;
	WaitForSingleObject(m_Mutex, INFINITE);
	BOOL bRes = WriteFile(m_hTerminatorPipe, &nVal, 4, &nNumberOfBytesWritten, NULL);
	ReleaseMutex(m_Mutex);

	CloseHandle(m_hTerminatorPipe);
}

PipeMgrAutoDeblockingReadInterface::~PipeMgrAutoDeblockingReadInterface() {
	if(m_bMutexInitialized) {
		string strError = "PipeMgrAutoDeblockingReadInterface::~PipeMgrAutoDeblockingReadInterface - ";

		WaitForSingleObject(m_Mutex, INFINITE);
		
		HANDLE hProccessSender = OpenProcess(
										 //PROCESS_ALL_ACCESS,//DWORD dwDesiredAccess,  // access flag
										 PROCESS_TERMINATE | PROCESS_QUERY_INFORMATION,//DWORD dwDesiredAccess,  // access flag
										 FALSE,//BOOL bInheritHandle,    // handle inheritance option
										 m_PIDAndHandle.m_PID//DWORD dwProcessId       // process identifier
										);
		BOOL bOk = hProccessSender != NULL;
		if(bOk == FALSE) {
			strError.append("Cannot duplicate handler");
			Singleton<Trace>::instance()->printWarningMessage(strError.c_str());
			ReleaseMutex(m_Mutex);
			return;
		}

		DWORD dwError;
		DWORD exitCode;
		BOOL bOkExitCode = GetExitCodeProcess(hProccessSender,&exitCode);
		if(bOkExitCode == 0) {
			dwError = GetLastError();
			strError.append("Last error due to GetExitCodeProcess was: " + itostr(dwError));
			Singleton<Trace>::instance()->printWarningMessage(strError.c_str());
		}
		BOOL bOkTerminateProcess = bOkExitCode && TerminateProcess(hProccessSender,exitCode);
		if(bOkTerminateProcess == 0) {
			dwError = GetLastError();
			strError.append("Last error due to TerminateProcess was: " + itostr(dwError));
			Singleton<Trace>::instance()->printWarningMessage(strError.c_str());
		}
		CloseHandle(hProccessSender);
		ReleaseMutex(m_Mutex);
	}
}