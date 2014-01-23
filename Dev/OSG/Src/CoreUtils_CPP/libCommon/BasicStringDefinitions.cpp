#include <windows.h>
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


bool isAtEndOfString(const std::string & astrName, const std::string & astrField)	{
	bool bRes = false;
	int nStrSize = sizeof(astrName);
//	int indexCh = astrName.find ( astrField ,  nStrSize - (nStrSize-sizeof(astrField)));
	int indexCh = astrName.find ( astrField ,  astrName.size() - astrField.size());
	if (indexCh != std::string::npos )
		bRes = true;
	return bRes;
}


vector<string> splitString(string & astrName, const string & astrDelimiters)	{
	vector<string> vecSplitString;
	int indexCh = 0;

	while (indexCh != string::npos) {
		indexCh = astrName.find_first_of(astrDelimiters);
		vecSplitString.push_back(astrName.substr(0,indexCh));
		astrName.erase(0, indexCh+1);
	}
	return vecSplitString;
}