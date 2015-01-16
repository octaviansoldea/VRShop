#include <string>

#include "Singleton.h"
#include "Trace.h"
#include "PipeMgrReadInterface.h"

using namespace std;

bool PipeMgrReadInterface::read(string & astrMessage) {

	if((m_bHandleInitialized == false) || (m_bSynchronizationInitialized == false))
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrReadInterface::read problems with pipe initialization");


	DWORD nNumberOfBytesRead;
	
	unsigned int nSizeOfInt = sizeof(int);

	BOOL bOk = FALSE;

    unsigned int nLength;

	bOk = ReadFile(m_hPipe, &nLength, sizeof(int), &nNumberOfBytesRead, NULL);
	if(bOk == FALSE) {
		Singleton<Trace>::instance()->printWarningMessage("Problems in reading from pipe");
		return(false);
	}
	if(nLength == 0) {
		astrMessage = "";
		return(true);
	} else {
		unsigned char * puchCurrRead = new unsigned char [nLength + 1];
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

