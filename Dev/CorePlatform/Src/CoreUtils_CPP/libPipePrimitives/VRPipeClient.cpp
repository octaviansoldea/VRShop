#include <string>
#include <iostream>
#include <fstream>

#include "VRPipeClient.h"

using namespace std;
using namespace VR;

PipeClient::PipeClient(std::string & astrPipeName) : m_strPipeName(astrPipeName)	{
	m_hPipe = NULL;
}

//--------------------------------------------------------------------------------

PipeClient::~PipeClient()	{
	if (m_hPipe != NULL)
		CloseHandle(m_hPipe);
}

//================================================================================

bool PipeClient::isPipeAccessible()	{
#if UNICODE
	LPCSTR lpszPipeName = m_strPipeName.str();
#else
	LPCSTR lpszPipeName = &m_strPipeName.front();
#endif //UNICODE

	// Try to open a named pipe; wait for it, if necessary.
	m_hPipe = CreateFile( 
		lpszPipeName,   // pipe name 
		GENERIC_READ,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);          // no template file ;

	if (GetLastError() == ERROR_SUCCESS)	{
		CloseHandle(m_hPipe);

		return true;
	}

	//If file can be accessed => parent is still alive
	bool bRes = ((GetLastError() == ERROR_FILE_NOT_FOUND) || (GetLastError() == ERROR_PIPE_NOT_CONNECTED)) ? false : true;

	return bRes;
}