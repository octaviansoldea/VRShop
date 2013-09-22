#include "StringManipulation.h"

using namespace std;

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
	int indexCh = astrName.find ( astrField ,  nStrSize - (nStrSize-sizeof(astrField)));
	if (indexCh != std::string::npos )
		bRes = true;
	return bRes;
}

std::vector<std::string> splitString(std::string & astrName, const std::string & astrDelimiters)	{
	vector<string> vecSplitString;
	int indexCh = 0;

	while (indexCh != string::npos) {
		indexCh = astrName.find_first_of(astrDelimiters);
		vecSplitString.push_back(astrName.substr(0,indexCh));
		astrName.erase(0, indexCh+1);
	}
	return vecSplitString;
}

//vector<string> splitString(string & astrName, const string & astrDelimiters)	{
//	vector<string> vecSplitString;
//	int indexCh = 0;
//
//	while (indexCh != string::npos) {
//		indexCh = astrName.find_first_of(astrDelimiters);
//		vecSplitString.push_back(astrName.substr(0,indexCh));
//		astrName.erase(0, indexCh+1);
//	}
//	return vecSplitString;
//}