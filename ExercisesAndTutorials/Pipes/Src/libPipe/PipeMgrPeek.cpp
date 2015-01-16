#include <string>

#include "Singleton.h"
#include "Trace.h"
#include "BasicStringDefinitions.h"
#include "PipeMgrPeek.h"

using namespace std;

bool PipeMgrPeek::peek(string & astrMessage) {

	string strError("PipeMgrReadInterface::read ");
	
	if((m_bHandleInitialized == false) || (m_bSynchronizationInitialized == false))
		Singleton<Trace>::instance()->printErrorMessage("PipeMgrReadInterface::read problems with pipe initialization");

	DWORD nNumberOfBytesRead;
	
	unsigned int nSizeOfInt = sizeof(int);

	BOOL bOk = FALSE;

    unsigned int nLength;

	DWORD nTotalBytesAvail;
	DWORD nBytesLeftThisMessage;


	bOk = PeekNamedPipe(
		m_hPipe,//HANDLE hNamedPipe,
		&nLength,//LPVOID lpBuffer,
		sizeof(int),//DWORD nBufferSize,
		&nNumberOfBytesRead,//LPDWORD lpBytesRead,
		&nTotalBytesAvail,//LPDWORD lpTotalBytesAvail,
		&nBytesLeftThisMessage//LPDWORD lpBytesLeftThisMessage
	);
	if(bOk == FALSE) {
		strError = GetLastErrorString();
		Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
	}
	if(nTotalBytesAvail == 0)
		return(false);
	while(nTotalBytesAvail < sizeof(int)) {
		bOk =  PeekNamedPipe(
			m_hPipe,//HANDLE hNamedPipe,
			&nLength,//LPVOID lpBuffer,
			sizeof(int),//DWORD nBufferSize,
			&nNumberOfBytesRead,//LPDWORD lpBytesRead,
			&nTotalBytesAvail,//LPDWORD lpTotalBytesAvail,
			&nBytesLeftThisMessage//LPDWORD lpBytesLeftThisMessage
		);
		if(bOk == FALSE) {
			strError = GetLastErrorString();
			Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
		}
	}
	bOk = ReadFile(m_hPipe, &nLength, sizeof(int), &nNumberOfBytesRead, NULL);
	if(bOk == FALSE) {
		strError = GetLastErrorString();
		Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
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
		bOk = true;
		nTotalBytesAvail = 0;
		while(nTotalBytesAvail < nLength) {
			bOk = PeekNamedPipe(
				m_hPipe,//HANDLE hNamedPipe,
				puchCurrRead,//LPVOID lpBuffer,
				nLength + sizeof(int),//DWORD nBufferSize,
				&nNumberOfBytesRead,//LPDWORD lpBytesRead,
				&nTotalBytesAvail,//LPDWORD lpTotalBytesAvail,
				&nBytesLeftThisMessage//LPDWORD lpBytesLeftThisMessage
			);
			if(bOk == FALSE) {
				delete [] puchCurrRead;
				strError = GetLastErrorString();
				Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
			}
			if(nTotalBytesAvail == nLength) {
				bOk = ReadFile(m_hPipe, puchCurrRead, nLength, &nNumberOfBytesRead, NULL);
				if(bOk == FALSE) {
					delete [] puchCurrRead;
					strError = GetLastErrorString();
					Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
				}
			}
			astrMessage = string((char *)puchCurrRead);
		}
		delete [] puchCurrRead;
	}
	return(true);

}

