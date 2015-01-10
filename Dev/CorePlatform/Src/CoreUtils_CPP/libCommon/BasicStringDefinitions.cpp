#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
#include <string>
#include <sstream>
//
//#include "BasicDefinitions.h"
#include "BasicStringDefinitions.h"

using namespace std;

#ifdef _WIN32
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
#else // _WIN32
std::string GetLastErrorString() {
   return("");
}
#endif //_WIN32

bool isInString(const std::string & astrName, const std::string & astrField) {
	bool bRes = false;
	int indexCh = astrName.find ( astrField , 0 );
	if (indexCh != std::string::npos )
		bRes = true;
	return(bRes);
}


bool isAtEndOfString(const std::string & astrName, const std::string & astrField)	{
	bool bRes = false;
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
	if (vecSplitString.back().empty())
		vecSplitString.pop_back();

	return vecSplitString;
}

std::string replaceAll(std::string astrText, const std::string& astrFrom, const std::string& astrTo) {
    size_t start_pos = 0;
    while((start_pos = astrText.find(astrFrom, start_pos)) != std::string::npos) {
        astrText.replace(start_pos, astrFrom.length(), astrTo);
        start_pos += astrTo.length(); // Handles case where 'to' is a substring of 'from'
    }
    return astrText;
}

//-------------------------------------------------------------------------------------------------

wstring string2WString(const string& astrString)	{
	std::wstring wstringString(astrString.begin(), astrString.end());
	return(wstringString);
}

//-------------------------------------------------------------------------------------------------

wchar_t * string2WChar(const std::string & astrString)	{
	//WARNING: RELEASE ALLOCATED MEMORY AT THE DECLARATION

	wchar_t * pWString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, astrString.c_str(), -1, pWString, 4096);

	return pWString;
}