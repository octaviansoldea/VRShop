#include <string>
#include <sys/stat.h>
#include <fstream>

#include "VRAppData.h"

using namespace std;
using namespace VR;

string AppData::m_strFPathVRShop = AppData::init();

//-----------------------------------------------------------------------------

string AppData::init() {
	char * pchPathVRShop = getenv("VRSHOP_CLIENT_PATH");
	string strRes = string(pchPathVRShop);
	return(strRes);
}

//-----------------------------------------------------------------------------

string AppData::getFPathVRShop() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppData::init();

	return(m_strFPathVRShop);
}

//-----------------------------------------------------------------------------

std::string AppData::getFPathDatabases() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppData::init();

	return(getFPathVRShop() + "/Databases/");
}

//-----------------------------------------------------------------------------

std::string AppData::getFPathLog() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppData::init();
	return(getFPathVRShop() + "/Log/");
}

//-----------------------------------------------------------------------------

std::string AppData::getFPathResources() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppData::init();
	return(getFPathVRShop() + "/Resources/");
}

//-----------------------------------------------------------------------------

std::string AppData::getFPathServer()	{
	string strResult = "http://127.0.0.1/Website";
	return strResult;
}

//-----------------------------------------------------------------------------

bool AppData::checkIfExists(const std::string & astrApplicationFolder)	{
	bool bRes = false;

	string strFileName = astrApplicationFolder;

	struct stat buffer;
	if (stat(strFileName.c_str(), &buffer) == 0)	//Return: 0 or -1
		bRes = true;

	return bRes;
}

//-----------------------------------------------------------------------------
