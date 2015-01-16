#include <string>
#include <iostream>

#include "VRAppData.h"
#include "BasicStringDefinitions.h"

#include <fstream>

#include <Windows.h>

#include "VRPipeServer.h"

using namespace std;
using namespace VR;

HANDLE ghJob = 0; // GLOBAL
PROCESS_INFORMATION pi;

class Process	{
public:
	Process();
	~Process();

	void newProcess(string & astrApplicationName, string & astrArguments);
};

Process::Process()	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	out << "Constructor process." << endl;

	out.close();
}

Process::~Process()	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	out << "Destructor process." << endl;

	out.close();

	// Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	CloseHandle(ghJob);
}


void Process::newProcess(string & astrApplicationName, string & astrArguments)	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	STARTUPINFO si = { sizeof(STARTUPINFO) };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	//Check the name of the pipe
	out << "newProcess: astrArguments: "  << astrArguments << endl;

	string strString = (astrApplicationName + " " + astrArguments);
	LPSTR lName = &strString.front();

	if( !CreateProcess( NULL,	// No module name (use command line).
		lName,				// Command line.
		NULL,					// Process handle not inheritable.
		NULL,					// Thread handle not inheritable.
		FALSE,					// Set handle inheritance to FALSE.
		NORMAL_PRIORITY_CLASS,	// No creation flags.
		NULL,					// Use parent's environment block.
		NULL,					// Use parent's starting directory.
		&si,					// Pointer to STARTUPINFO structure.
		&pi )					// Pointer to PROCESS_INFORMATION structure.
		)	{

			out << "Process not created." << endl;
			out.close();
			return;
	}

	out << "Process created.\n" << "ghJob: " << ghJob << endl;
	out.close();
}

//=======================================================================================

int main_Blocking(int argc, char * argv[]) {
	//string strExe = "C:\\Projekti\\VRShop\\ExercisesAndTutorials\\Pipes\\Build\\Test_libModel\\Debug\\Test_libModel.exe";
	string strExe = 
		replaceAll(AppData::getFPathVRShop(),"/","\\") + 
		"\\..\\..\\ExercisesAndTutorials\\Pipes\\Build\\Test_libModel\\Debug\\Test_libModel.exe";
	string strPipeName = "\\\\.\\pipe\\mynamedpipe";

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);

	//Create pipe server
	PipeServer pipeServer;
	pipeServer.initializeAndRunServer(strPipeName);

	//Create process
	ghJob = CreateJobObject(NULL, NULL);
	if (ghJob == NULL)	{
		out << "Could not create job object" << endl;
	} else {
		JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };

		// Configure all child processes associated with the job to terminate when the
		jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
		if( 0 == SetInformationJobObject( ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))	{
			out << "Could not SetInformationJobObject" << endl;
		}
	}

	out.close();

	Process process;
	process.newProcess(strExe,strPipeName);

	return 0;
}

//=======================================================================

int main(int argc, char * argv[])	{
	main_Blocking(argc,argv);
}