#include <windows.h>
#include <string>
#include <sstream>

#include "BasicDefinitions.h"
#include "BasicStringDefinitions.h"

using namespace std;

std::string itostr(int anVal) {
	
   stringstream ss;//create a stringstream
   ss << anVal;//add number to the stream
   return ss.str();//return a string with the contents of the stream

}

std::string GetLastErrorString() {
	LPVOID lpMsgBuf;
	DWORD dw = GetLastError(); 

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		dw,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR) &lpMsgBuf,
		0,
		NULL );

		//printf("failed with error %d: %s", dw, lpMsgBuf); 
		std::string strVal((char *)lpMsgBuf);
		LocalFree(lpMsgBuf);
		return(strVal);

}

bool isInString(const std::string & astrName, const std::string & astrField) {
	bool bRes = false;
	int indexCh = astrName.find ( astrField , 0 );
	if (indexCh != std::string::npos )
		bRes = true;
	return(bRes);
}