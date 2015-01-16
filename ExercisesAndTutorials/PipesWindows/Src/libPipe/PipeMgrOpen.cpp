#include <string>
#include "BasicStringDefinitions.h"

#include "Singleton.h"
#include "Trace.h"
#include "PipeMgrOpen.h"

using namespace std;

bool PipeMgrOpen::openPipe(DWORD adwDesiredAccess) {
	if(m_bHandleInitialized) {
		printf("Error: Reinitialization of a handle that was already set");
		return(false);
	}

	if((adwDesiredAccess != GENERIC_READ) && (adwDesiredAccess != GENERIC_WRITE)) {
		Singleton<Trace>::instance()->printWarningMessage("Problems in open mode specifications");
		return(false);
	}

	m_dwMode = adwDesiredAccess;
	//m_strPipeName = apchPipeName;
#if UNICODE
	LPCTSTR lpName = string2WString(m_strPipeName).c_str();
#else
	LPCTSTR lpName = m_strPipeName.c_str();
#endif	
	//Waits until the specified object is in the signaled state or the time-out interval elapses.
	WaitForSingleObject(m_hSynchronizationEvent, INFINITE);
	m_hPipe = CreateFile(
		lpName,                         // file name
		//GENERIC_READ,                      // access mode
		adwDesiredAccess,
		0,                          // share mode
		NULL, // SD
		OPEN_EXISTING,//CREATE_ALWAYS                // how to create
		FILE_ATTRIBUTE_NORMAL,                 // file attributes
		NULL                        // handle to template file
		);
	if(m_hPipe == INVALID_HANDLE_VALUE) {
		DWORD dwErr = GetLastError();
		printf("Error: Cannot open (file - second handle) named %s\n", lpName);
		printf("The error code detected was: %d\n", dwErr);
		return(false);
	}

	m_bHandleInitialized = true;

	return(true);
}
