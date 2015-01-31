#include <string>
#include <sys/stat.h>
#include <fstream>

#include "VRAppDataServer.h"

using namespace std;
using namespace VR;

string AppDataServer::m_strFPathVRShop = AppDataServer::init();

//-----------------------------------------------------------------------------

string AppDataServer::init() {
	char * pchPathVRShop = getenv("VRSHOP_SERVER_PATH");
	string strRes = string(pchPathVRShop);
	return(strRes);
}

//-----------------------------------------------------------------------------

string AppDataServer::getFPathVRShop() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppDataServer::init();
	return(m_strFPathVRShop);
}

//-----------------------------------------------------------------------------

std::string AppDataServer::getFPathDatabases() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppDataServer::init();

	return(getFPathVRShop() + "/Databases/");
}

//-----------------------------------------------------------------------------

std::string AppDataServer::getFPathLog() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppDataServer::init();
	return(getFPathVRShop() + "/Log/");
}

//-----------------------------------------------------------------------------

std::string AppDataServer::getFPathResources() {
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppDataServer::init();
	return(getFPathVRShop() + "/Resources/");
}

//-----------------------------------------------------------------------------

std::string AppDataServer::getFPathDependencies()	{
	if(m_strFPathVRShop == "")
		m_strFPathVRShop = AppDataServer::init();
	return(getFPathVRShop() + "/plugins/");
}

//-----------------------------------------------------------------------------

std::string AppDataServer::getFPathServer()	{
	string strResult = "http://127.0.0.1/Website";
	return strResult;
}

//-----------------------------------------------------------------------------

bool AppDataServer::checkIfExists(const std::string & astrApplicationFolder)	{
	bool bRes = false;

	string strFileName = astrApplicationFolder;

	struct stat buffer;
	if (stat(strFileName.c_str(), &buffer) == 0)	//Return: 0 or -1
		bRes = true;

	return bRes;
}

//-----------------------------------------------------------------------------
