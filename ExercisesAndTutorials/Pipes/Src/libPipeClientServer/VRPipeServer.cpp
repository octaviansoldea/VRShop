#include <string>
#include <fstream>

#include "VRPipeServer.h"

using namespace std;
using namespace VR;

PipeServer::PipeServer()	{
	//m_hEvents = NULL;

	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);

	out << "PipeServer constructor" << endl;
	out.close();
}

//-------------------------------------------------------------------

PipeServer::~PipeServer()	{
	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);

	out << "PipeServer destructor" << endl;

	out.close();

	//if (m_hEvents == NULL)
	//	closeServer();
}

//===================================================================

bool PipeServer::initializeAndRunServer(std::string & astrPipeName)	{
	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);

	out << "PipeServer constructor; astrPipeName: " << astrPipeName << endl;
	m_lpszPipeName = astrPipeName.c_str();
	out << "Pipe server m_lpszPipeName: " << m_lpszPipeName << endl;

	//m_hEvents = CreateEvent( 
	//	NULL,    // default security attribute 
	//	TRUE,    // manual-reset event 
	//	TRUE,    // initial state = signaled 
	//	NULL);   // unnamed event object 

	//if (m_hEvents == NULL)	{
	//	printf("CreateEvent failed with %d.\n", GetLastError()); 
	//	return false;
	//}

	LPCSTR lpPipeName = m_lpszPipeName;

	HANDLE hPipe = CreateNamedPipe( 
		lpPipeName,            // pipe name 
		PIPE_ACCESS_DUPLEX |     // read/write access 
		FILE_FLAG_OVERLAPPED,    // overlapped mode 
		PIPE_TYPE_MESSAGE |      // message-type pipe 
		PIPE_READMODE_MESSAGE |  // message-read mode 
		PIPE_WAIT,               // blocking mode 
		1,               // number of instances 
		0,   // output buffer size 
		0,   // input buffer size 
		2000,            // client time-out 
		NULL);                   // default security attributes 

	if (hPipe == INVALID_HANDLE_VALUE)	{
		printf("CreateNamedPipe failed with %d.\n", GetLastError());
		return false;
	}

	return true;
}

//-------------------------------------------------------------------

void PipeServer::closeServer()	{
	//CloseHandle(m_hEvents);
}
