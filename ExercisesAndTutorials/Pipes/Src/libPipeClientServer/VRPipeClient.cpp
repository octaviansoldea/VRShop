#include <string>
#include <iostream>
#include <fstream>

#include "VRPipeClient.h"

using namespace std;
using namespace VR;

PipeClient::PipeClient(std::string & astrPipeName)	{
	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);
	out << "PipeClient constructor; astrPipeName: " << astrPipeName << endl;
	out.close();

	m_lpszPipeName = astrPipeName.c_str();
	m_hPipe = NULL;
}

//--------------------------------------------------------------------------------

PipeClient::~PipeClient()	{
	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);
	out << "PipeClient destructor" << endl;
	out.close();

	if (m_hPipe != NULL)
		CloseHandle(m_hPipe);
}

//================================================================================

bool PipeClient::isPipeAccessible()	{
	ofstream out;
	string strLog = "C:/Projekti/VRShop/ExercisesAndTutorials/Pipes/Log.txt";
	out.open(strLog,ios::app);
	out << "isPipeAccessible" << endl;
	out.close();

	// Try to open a named pipe; wait for it, if necessary.
	m_hPipe = CreateFile( 
		m_lpszPipeName,   // pipe name 
		GENERIC_READ,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);          // no template file ;

	//If file can be accessed => parent is still alive
	bool bRes = (GetLastError() != ERROR_FILE_NOT_FOUND);

	return bRes;
}