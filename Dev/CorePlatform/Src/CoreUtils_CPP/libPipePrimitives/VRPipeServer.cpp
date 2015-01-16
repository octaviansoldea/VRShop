#include <string>

#include "BasicStringDefinitions.h"

#include "VRPipeServer.h"

using namespace std;
using namespace VR;

PipeServer::PipeServer()	{
	m_hEvents = NULL;
}

//-------------------------------------------------------------------

PipeServer::~PipeServer()	{
	closeServer();
}

//===================================================================

bool PipeServer::initializeAndRunServer(std::string & astrPipeName)	{
	m_hEvents = CreateEvent( 
		NULL,    // default security attribute 
		TRUE,    // manual-reset event 
		TRUE,    // initial state = signaled 
		NULL);   // unnamed event object 

	if (m_hEvents == NULL)	{
		return false;
	}

#if UNICODE
	wchar_t * wstr = string2WChar(astrPipeName);
	LPCWSTR lpPipeName = wstr;
#else
	LPCSTR lpPipeName = astrPipeName.c_str();
#endif
	m_hPipe = CreateNamedPipe(
		lpPipeName,				// pipe name
		PIPE_ACCESS_DUPLEX |	// read/write access
		FILE_FLAG_OVERLAPPED,	// overlapped mode
		PIPE_TYPE_MESSAGE |		// message-type pipe
		PIPE_READMODE_MESSAGE |	// message-read mode
		PIPE_WAIT,				// blocking mode
		1,						// number of instances
		0,						// output buffer size
		0,						// input buffer size
		2000,					// client time-out
		NULL);					// default security attributes

	if (m_hPipe == INVALID_HANDLE_VALUE)	{
#if UNICODE
	delete [] wstr;
#endif //UNICODE
		return false;
	}

#if UNICODE
	delete [] wstr;
#endif //UNICODE

	return true;
}

//-------------------------------------------------------------------

void PipeServer::closeServer()	{
	//DisconnectNamedPipe makes the client's handle invalid, if it has not already been closed.
	if (DisconnectNamedPipe(m_hPipe) == 0)	{

	} else {

	}

	//Server closes its handle to the pipe instance
	CloseHandle(m_hEvents);
	CloseHandle(m_hPipe);
}
