#ifdef _WIN32
#include <windows.h>
#endif //_WIN32
#include <string>
#include <sstream>
//
//#include "BasicDefinitions.h"

#include <bitset>
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

//-------------------------------------------------------------------------------------------------

bool isInString(const std::string & astrName, const std::string & astrField) {
	bool bRes = false;
	int indexCh = astrName.find ( astrField , 0 );
	if (indexCh != std::string::npos )
		bRes = true;
	return(bRes);
}

//-------------------------------------------------------------------------------------------------

bool isAtEndOfString(const std::string & astrName, const std::string & astrField)	{
	int nDataSize = astrField.size();
	int nNameSize = astrName.size();
	char * pchStr = new char[nDataSize+1];
	memcpy(pchStr, &astrName[0] + sizeof(char)*(nNameSize-nDataSize), sizeof(char)*(nDataSize+1));

	bool bRes = (strcmp(pchStr, astrField.c_str()) == 0);
	delete [] pchStr;

	return bRes;
}

//-------------------------------------------------------------------------------------------------

vector<string> splitString(string & astrName, char * astrDelimiters)	{
	char * pchData = &astrName[0];
	char * pch;
	vector<string> vecSplitString;

	pch = strtok(pchData, astrDelimiters);
	while (pch != NULL)	{
		vecSplitString.push_back(pch);
		pch = strtok(NULL, astrDelimiters);
	}

	return vecSplitString;
}

//-------------------------------------------------------------------------------------------------

std::string replaceAll(std::string astrText, const std::string& astrFrom, const std::string& astrTo) {
    size_t start_pos = 0;
    while((start_pos = astrText.find(astrFrom, start_pos)) != std::string::npos) {
        astrText.replace(start_pos, astrFrom.length(), astrTo);
        start_pos += astrTo.length(); // Handles case where 'to' is a substring of 'from'
    }
    return astrText;
}

//-------------------------------------------------------------------------------------------------

void trimString(std::string * apstrSource, char * apchDelim, std::string & astrTarget)	{
	int nDataSize = apstrSource->size();
	char * pchStr = new char[nDataSize+1];
	memcpy(pchStr, &*apstrSource->begin(), nDataSize+1);
	char * pch = strtok(pchStr, apchDelim);
	astrTarget = apstrSource->substr(strlen(pch)+1,nDataSize);
	delete [] pchStr;
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


//===================================================================

void splitString(string const& s, char const* d, vector<string> & avecstrResult)	{
	bitset<255> delims;
	while(*d)	{
		unsigned char code = *d++;
		delims[code] = true;
	}
	string::const_iterator iter;
	bool in_token = false;
	for(string::const_iterator it = s.begin(), end = s.end(); it != end; ++it)	{
		if(delims[*it])	{
			if(in_token)	{
				avecstrResult.push_back(string(iter,it));
				in_token = false;
			}
		} else if(!in_token) {
			iter = it;
			in_token = true;
		}
	}
	if(in_token)
		avecstrResult.push_back(string(iter,s.end()));
}