#ifdef _WIN32
#include <sys/stat.h>
#endif //_WIN32

// Left here for requiring implementations
#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
#ifdef __linux__
#endif
#ifdef __unix__
#endif
#ifdef __APPLE__
#endif


#include <stdio.h>
#include <string>
#include <exception>

#include "BasicStringDefinitions.h"
#include "Singleton.h"
#include "Trace.h"
#include "FileOperations.h"

using namespace std;

#ifdef _WIN32
unsigned __int64 GetFileSizeFromName(const char * astrFileName) {
	
	/*
	char arrchError[MAX_STR_LEN];

	LPCTSTR lpFileName = astrFileName;
	HANDLE hFile = CreateFile(
		lpFileName, // file name
		GENERIC_READ, // access mode
		0, // share mode
		NULL, // SD
		OPEN_EXISTING, // how to create
		FILE_ATTRIBUTE_NORMAL, // file attributes
		NULL // handle to template file
		);
	if(hFile == INVALID_HANDLE_VALUE) {
		sprintf(arrchError, "Problem in GetFileSizeFromName - cannot open file %s", astrFileName);
		Singleton<Trace>::instance()->printWarningMessage(arrchError);
		DWORD dwErr = GetLastError();
		sprintf(arrchError, "The error code detected was: %d", dwErr);
		Singleton<Trace>::instance()->printWarningMessage(arrchError);
		exit(-1);
	}

	DWORD nFileSize = GetFileSize(hFile, NULL);
	CloseHandle(hFile);
	if(nFileSize == INVALID_FILE_SIZE) {
		sprintf(arrchError, "Problem in GetFileSizeFromName - file %s size could not be evaluated", astrFileName);
		Singleton<Trace>::instance()->printWarningMessage(arrchError);
		exit(-1);
	}
	return(nFileSize);
	*/

	struct _stati64 st;
	unsigned __int64 nFileSize;
	if (_stati64(astrFileName,&st) < 0) {
		string strError = string("GetFileSizeFromName: negative file size ") + string(astrFileName) + string("\n");
		Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
	}
	nFileSize = st.st_size;
	return(nFileSize);
}

#endif //_WIN32

void CheckedFileOpen(FILE ** appfp, const string & astrFileName, const char * apchMode) {
	(*appfp) = fopen(astrFileName.c_str(), apchMode);//"wb");
	if((*appfp) == NULL) {
		string strError = "CheckedFileOpen: Problem when open file " + astrFileName;
		Singleton<Trace>::instance()->printErrorMessage(strError.c_str());
	}
}



const char* ExceptionSuffix::what() const throw() {
    return "Cannot find suffix";
}

string getSuffix(const string & astrFileName) {
	int nLen = astrFileName.length();

	if((nLen < 4) || (astrFileName.substr(nLen - 4, 1) != ".")) {
		throw(ExceptionSuffix());
	}
	
	string strSuffix = astrFileName.substr(nLen - 3, nLen - 1);
	return(strSuffix);
}

string adjustFileData(std::string & strFileDir, std::string & strFileName)	{
	strFileDir += (isAtEndOfString(strFileDir, "/")) ? "" : "/";
	strFileDir += strFileName;
	strFileDir += (isAtEndOfString(strFileDir, ".db")) ? "" : ".db";
	string strFileNameFinal = replaceAll(strFileDir, "/", "\\");

	return strFileNameFinal;
}