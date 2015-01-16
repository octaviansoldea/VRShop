#include <windows.h> 
#include <stdio.h>
#include <conio.h>
#include <tchar.h>
#include <iostream> 

using namespace std;

int main(int argc, char *argv[])	{
	HANDLE hPipe; 
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); 

	// Try to open a named pipe; wait for it, if necessary.
	do {
		hPipe = CreateFile( 
			lpszPipename,   // pipe name 
			GENERIC_READ,
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			0,              // default attributes 
			NULL);          // no template file ;
		cout << "pipe is still alive" << endl;
	} while (GetLastError() != ERROR_FILE_NOT_FOUND);

	CloseHandle(hPipe); 

	return 0; 
}

//-------------------------------------------------------------
