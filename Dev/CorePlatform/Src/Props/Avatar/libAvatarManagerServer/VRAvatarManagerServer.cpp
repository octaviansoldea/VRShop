#include "BasicStringDefinitions.h"

#include <time.h>

#include "VRDatabaseInterface.h"

#include "VRAvatarManagerServer.h"


using namespace VR;
using namespace std;

#define DEBUG_AVATARS 0

DatabaseInterface AvatarManagerServer::m_DIAvatar(
	DatabaseInterfaceParams(AvatarManagerServer::getDatabaseName().c_str(),"Avatar")
);

//==============================================================================

AvatarManagerServer::AvatarManagerServer()	{
}

//------------------------------------------------------------------------------

AvatarManagerServer::~AvatarManagerServer()	{
}

//------------------------------------------------------------------------------

const char* AvatarManagerServer::className() const	{
	return "AvatarManagerServer";
}

//------------------------------------------------------------------------------

void AvatarManagerServer::registerAvatar(string & astrRequest)	{
	vector<string> vecstrSplitString = splitString(astrRequest,";");

	string strSqlQuery = "INSERT INTO Avatar(AvatarName, AvatarMatrix) VALUES ('" + 
		vecstrSplitString[0] + "','" + vecstrSplitString[1] + "')";

	DatabaseInterface *pDI = AvatarManagerServer::getDatabaseInterface();
	pDI->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

void AvatarManagerServer::updateAvatarData(std::string & astrRequest)	{
	vector<string> vecstrSplitString = splitString(astrRequest,";");
	string strSqlQuery = "UPDATE Avatar" 
		" SET AvatarMatrix = '" + vecstrSplitString[1] + 
//		"', AvatarDateTime = CURRENT_TIMESTAMP" + 
		"', AvatarDateTime = '" + tostr(time(NULL)
										//m_pTimer->getCurrTimeInMiliSeconds()
										) + "'"+ 
		" WHERE AvatarName = '" + vecstrSplitString[0] + "'";

	DatabaseInterface *pDI = AvatarManagerServer::getDatabaseInterface();
	pDI->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

list<string> AvatarManagerServer::getAvatarsDataFromDB()	{
#if DEBUG_AVATARS
	vector<string> vecstrSplitString = splitString(astrRequest,";");
	int nI;
	string strSqlCondition = "'" + vecstrSplitString[0] + "'";
	for (nI=1;nI<vecstrSplitString.size();nI++)	{
		strSqlCondition += " OR AvatarName = '" + vecstrSplitString[nI] + "'";
	}
	strSqlQuery = "SELECT * FROM Avatar WHERE AvatarName = " + strSqlCondition;
#else
	string strSqlQuery = "SELECT AvatarName, AvatarMatrix FROM Avatar";
#endif //DEBUG_AVATAR

	DatabaseInterface *pDI = AvatarManagerServer::getDatabaseInterface();
	
	list<string> lststrResult = pDI->executeAndGetResult(strSqlQuery);

	return lststrResult;
}


//====================================================================================================

string AvatarManagerServer::getTableName()	{
	return "Avatar";
}

//------------------------------------------------------------------------------

string AvatarManagerServer::getDatabaseName()	{
	return "../../../../Databases/Avatars.db";
}

//------------------------------------------------------------------------------

vector<pair<string,string>> AvatarManagerServer::getAvatarElements()	{
	vector<pair<string,string>> vecpairAvatarElements;

	vecpairAvatarElements.push_back(make_pair("AvatarID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairAvatarElements.push_back(make_pair("AvatarName", "TEXT"));
	vecpairAvatarElements.push_back(make_pair("AvatarMatrix", "TEXT"));
	vecpairAvatarElements.push_back(make_pair("AvatarDateTime", "TEXT"));

	return vecpairAvatarElements;
}

//------------------------------------------------------------------------------

void AvatarManagerServer::createAvatarDB() const	{
	m_DIAvatar.createTable(getTableName(), getAvatarElements());
}

//------------------------------------------------------------------------------

DatabaseInterface * AvatarManagerServer::getDatabaseInterface() {
	return(&m_DIAvatar);
}
