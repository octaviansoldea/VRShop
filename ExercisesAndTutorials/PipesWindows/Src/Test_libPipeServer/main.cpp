#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <strsafe.h>
#include <iostream> 

using namespace std;

#define CONNECTING_STATE 0 
#define READING_STATE 1 
#define WRITING_STATE 2 
#define PIPE_TIMEOUT 5000
#define BUFSIZE 4096

typedef struct	{ 
	OVERLAPPED oOverlap; 
	HANDLE hPipeInst; 
	TCHAR chRequest[BUFSIZE]; 
	DWORD cbRead;
	TCHAR chReply[BUFSIZE];
	DWORD cbToWrite; 
	DWORD dwState; 
	BOOL fPendingIO; 
} PIPEINST, *LPPIPEINST; 


VOID DisconnectAndReconnect(); 
BOOL ConnectToClient(HANDLE, LPOVERLAPPED); 
VOID GetAnswerToRequest(LPPIPEINST); 

bool createHandle(std::string & astrPipeName);

PIPEINST Pipe; 
HANDLE hEvents; 

int main(int argc, char *argv[])	{ 
	DWORD dwWait, cbRet, dwErr; 
	BOOL fSuccess; 
	LPTSTR lpszPipename = TEXT("\\\\.\\pipe\\mynamedpipe"); 

	// The initial loop creates several instances of a named pipe 
	// along with an event object for each instance.  An 
	// overlapped ConnectNamedPipe operation is started for 
	// each instance. 

	// Create an event object for this instance.

	string strPipeName = string(lpszPipename);
	bool bRes = createHandle(strPipeName);


	//==================================
	for (int nI = 0;nI<10;nI++)	{
		cout << nI << endl;
	}

	// Call the subroutine to connect to the new client
	Pipe.fPendingIO = ConnectToClient(
		Pipe.hPipeInst,
		&Pipe.oOverlap);

	Pipe.dwState = Pipe.fPendingIO ? 
			CONNECTING_STATE : // still connecting 
			READING_STATE;     // ready to read 

	while (1)	{ 
		// Wait for the event object to be signaled, indicating 
		// completion of an overlapped read, write, or 
		// connect operation. 

		dwWait = WaitForSingleObject(
			hEvents,      // array of event objects 
			INFINITE);    // waits indefinitely 

		// Get the result if the operation was pending. 

		if (Pipe.fPendingIO)	{ 
			fSuccess = GetOverlappedResult( 
				Pipe.hPipeInst, // handle to pipe 
				&Pipe.oOverlap, // OVERLAPPED structure 
				&cbRet,            // bytes transferred 
				FALSE);            // do not wait 

			switch (Pipe.dwState) 
			{ 
				// Pending connect operation 
			case CONNECTING_STATE: 
				if (! fSuccess ) 
				{
					printf("Error %d.\n", GetLastError()); 
					return 0;
				}
				Pipe.dwState = READING_STATE; 
				break; 

				// Pending read operation 
			case READING_STATE: 
				if (! fSuccess || cbRet == 0) 
				{ 
					DisconnectAndReconnect(); 
					continue; 
				}
				Pipe.cbRead = cbRet;
				Pipe.dwState = WRITING_STATE; 
				break; 

				// Pending write operation 
			case WRITING_STATE: 
				if (! fSuccess || cbRet != Pipe.cbToWrite) 
				{ 
					DisconnectAndReconnect(); 
					continue; 
				} 
				Pipe.dwState = READING_STATE; 
				break; 

			default: 
				{
					printf("Invalid pipe state.\n"); 
					return 0;
				}
			}  
		} 

		// The pipe state determines which operation to do next. 

		switch (Pipe.dwState) 
		{ 
			// READING_STATE: 
			// The pipe instance is connected to the client 
			// and is ready to read a request from the client. 

		case READING_STATE: 
			fSuccess = ReadFile( 
				Pipe.hPipeInst, 
				Pipe.chRequest, 
				BUFSIZE*sizeof(TCHAR), 
				&Pipe.cbRead, 
				&Pipe.oOverlap); 

			// The read operation completed successfully. 
			if (fSuccess && Pipe.cbRead != 0)	{ 
				Pipe.fPendingIO = FALSE;
				Pipe.dwState = WRITING_STATE;
				continue;
			}

			// The read operation is still pending.
			dwErr = GetLastError();
			if (! fSuccess && (dwErr == ERROR_IO_PENDING))	{ 
				Pipe.fPendingIO = TRUE;
				continue;
			}

			// An error occurred; disconnect from the client. 
			DisconnectAndReconnect();
			break;

			// WRITING_STATE: 
			// The request was successfully read from the client. 
			// Get the reply data and write it to the client. 

		case WRITING_STATE: 
			GetAnswerToRequest(&Pipe); 

			fSuccess = WriteFile( 
				Pipe.hPipeInst, 
				Pipe.chReply, 
				Pipe.cbToWrite, 
				&cbRet, 
				&Pipe.oOverlap); 

			// The write operation completed successfully. 

			if (fSuccess && cbRet == Pipe.cbToWrite) 
			{ 
				Pipe.fPendingIO = FALSE; 
				Pipe.dwState = READING_STATE; 
				continue; 
			} 

			// The write operation is still pending. 

			dwErr = GetLastError(); 
			if (! fSuccess && (dwErr == ERROR_IO_PENDING)) 
			{ 
				Pipe.fPendingIO = TRUE; 
				continue; 
			} 

			// An error occurred; disconnect from the client. 

			DisconnectAndReconnect(); 
			break; 

		default: 
			{
				printf("Invalid pipe state.\n"); 
				return 0;
			}
		} 
	} 

	return 0; 
} 


// DisconnectAndReconnect(DWORD) 
// This function is called when an error occurs or when the client 
// closes its handle to the pipe. Disconnect from this client, then 
// call ConnectNamedPipe to wait for another client to connect. 

VOID DisconnectAndReconnect()	{ 
	// Disconnect the pipe instance. 

	if (! DisconnectNamedPipe(Pipe.hPipeInst) ) 
	{
		printf("DisconnectNamedPipe failed with %d.\n", GetLastError());
	}

	// Call a subroutine to connect to the new client. 

	Pipe.fPendingIO = ConnectToClient( 
		Pipe.hPipeInst, 
		&Pipe.oOverlap); 

	Pipe.dwState = Pipe.fPendingIO ? 
CONNECTING_STATE : // still connecting 
	READING_STATE;     // ready to read 
} 

// ConnectToNewClient(HANDLE, LPOVERLAPPED) 
// This function is called to start an overlapped connect operation. 
// It returns TRUE if an operation is pending or FALSE if the 
// connection has been completed. 

BOOL ConnectToClient(HANDLE hPipe, LPOVERLAPPED lpo)	{ 
	BOOL fConnected, fPendingIO = FALSE; 

	// Start an overlapped connection for this pipe instance. 
	fConnected = ConnectNamedPipe(hPipe, lpo); 

	// Overlapped ConnectNamedPipe should return zero. 
	if (fConnected) 
	{
		printf("ConnectNamedPipe failed with %d.\n", GetLastError()); 
		return 0;
	}

	switch (GetLastError()) 
	{ 
		// The overlapped connection in progress. 
	case ERROR_IO_PENDING: 
		fPendingIO = TRUE; 
		break; 

		// Client is already connected, so signal an event. 

	case ERROR_PIPE_CONNECTED: 
		if (SetEvent(lpo->hEvent)) 
			break; 

		// If an error occurs during the connect operation... 
	default: 
		{
			printf("ConnectNamedPipe failed with %d.\n", GetLastError());
			return 0;
		}
	} 

	return fPendingIO; 
}

VOID GetAnswerToRequest(LPPIPEINST pipe)
{
	_tprintf( TEXT("[%d] %s\n"), pipe->hPipeInst, pipe->chRequest);
	StringCchCopy( pipe->chReply, BUFSIZE, TEXT("Default answer from server") );
	pipe->cbToWrite = (lstrlen(pipe->chReply)+1)*sizeof(TCHAR);
}


bool createHandle(std::string & astrPipeName)	{
	hEvents = CreateEvent( 
		NULL,    // default security attribute 
		TRUE,    // manual-reset event 
		TRUE,    // initial state = signaled 
		NULL);   // unnamed event object 

	if (hEvents == NULL)	{
		printf("CreateEvent failed with %d.\n", GetLastError()); 
		return 0;
	}

	Pipe.oOverlap.hEvent = hEvents;

	LPCSTR lpPipeName = astrPipeName.c_str();

	Pipe.hPipeInst = CreateNamedPipe( 
		lpPipeName,            // pipe name 
		PIPE_ACCESS_DUPLEX |     // read/write access 
		FILE_FLAG_OVERLAPPED,    // overlapped mode 
		PIPE_TYPE_MESSAGE |      // message-type pipe 
		PIPE_READMODE_MESSAGE |  // message-read mode 
		PIPE_WAIT,               // blocking mode 
		1,               // number of instances 
		BUFSIZE*sizeof(char),   // output buffer size 
		BUFSIZE*sizeof(char),   // input buffer size 
		PIPE_TIMEOUT,            // client time-out 
		NULL);                   // default security attributes 

	if (Pipe.hPipeInst == INVALID_HANDLE_VALUE)	{
		printf("CreateNamedPipe failed with %d.\n", GetLastError());
		return 0;
	}

	return 1;
}