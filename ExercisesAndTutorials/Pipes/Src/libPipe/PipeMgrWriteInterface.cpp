#include "Singleton.h"
#include "Trace.h"
#include "PipeMgrWriteInterface.h"

bool PipeMgrWriteInterface::write(const unsigned char * apuchMessage, int anLength) {

	if((m_bHandleInitialized == false) || (m_bSynchronizationInitialized == false))
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrWriteInterface::write problems with pipe initialization");


	DWORD nNumberOfBytesWritten = 0;
	BOOL bOk = WriteFile(m_hPipe, &anLength, sizeof(int), &nNumberOfBytesWritten, NULL);
	bOk = bOk && WriteFile(m_hPipe, apuchMessage, anLength, &nNumberOfBytesWritten, NULL);
	if(!bOk) {
		DWORD dwErr = GetLastError();
		Singleton<Trace>::instance()->printWarningMessage("Cannnot write to named pipe");
		printf("The error code detected was: %d\n", dwErr);
	}
	return(!!bOk);
	
}