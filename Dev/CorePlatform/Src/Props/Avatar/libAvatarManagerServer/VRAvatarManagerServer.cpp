#include "BasicStringDefinitions.h"

#include "VRAppDataServer.h"

#include <time.h>

#include "VRDatabaseInterface.h"

#include "VRAvatarManagerServer.h"


using namespace VR;
using namespace std;

#define DEBUG_AVATARS 0

DatabaseInterface * AvatarManagerServer::m_pDIAvatar = 0;

//==============================================================================

AvatarManagerServer::AvatarManagerServer()	{
}

//------------------------------------------------------------------------------

const char* AvatarManagerServer::className() const	{
	return "AvatarManagerServer";
}

//------------------------------------------------------------------------------

DatabaseInterfaceParams AvatarManagerServer::getDBParams()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "Avatar";
	dbParams.m_qstrDBName = getDatabaseName().c_str();

	return dbParams;
}

//------------------------------------------------------------------------------

void AvatarManagerServer::registerAvatar(string & astrAvatarName, string & astrAvatarMatrix)	{
	string strSqlQuery = "INSERT INTO Avatar(AvatarName, AvatarMatrix, AvatarDateTime) VALUES ('" + 
		astrAvatarName + "','" + astrAvatarMatrix + "',0)";

	DatabaseInterface *pDI = AvatarManagerServer::getDatabaseInterface();
	pDI->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

void AvatarManagerServer::updateAvatarData(std::string & astrAvatarName, std::string & astrAvatarMatrix)	{
	string strSqlQuery = "UPDATE Avatar" 
		" SET AvatarMatrix = '" + astrAvatarMatrix + 
//		"', AvatarDateTime = CURRENT_TIMESTAMP" + 
		"', AvatarDateTime = '" + tostr(time(NULL)
										//m_pTimer->getCurrTimeInMiliSeconds()
										) + "'"+ 
		" WHERE AvatarName = '" + astrAvatarName + "'";

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
	string strDBName = AppDataServer::getFPathDatabases() + "Avatars.db";
	return(strDBName);
}

//------------------------------------------------------------------------------

vector<pair<string,string>> AvatarManagerServer::getDBElements()	{
	vector<pair<string,string>> vecpairAvatarElements;

	vecpairAvatarElements.push_back(make_pair("AvatarID", "INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE"));
	vecpairAvatarElements.push_back(make_pair("AvatarName", "TEXT"));
	vecpairAvatarElements.push_back(make_pair("AvatarMatrix", "TEXT"));
	vecpairAvatarElements.push_back(make_pair("AvatarDateTime", "TEXT"));

	return vecpairAvatarElements;
}

//------------------------------------------------------------------------------

void AvatarManagerServer::createAvatarDB() {
	m_pDIAvatar->createTable(getTableName(), getDBElements());
}

//------------------------------------------------------------------------------

DatabaseInterface * AvatarManagerServer::getDatabaseInterface() {
	return(m_pDIAvatar);
}

//------------------------------------------------------------------------------

void AvatarManagerServer::checkAvatarActivity()	{
	long lTime = time(NULL) - 10;

	string strSqlQueryDelete = "DELETE FROM Avatar WHERE (AvatarDateTime > 0) AND (AvatarDateTime < '" + 
						tostr(lTime)
						//m_pTimer->getCurrTimeInMiliSeconds()
						+ "')"
						;

	m_pDIAvatar->executeAndGetResult(strSqlQueryDelete);

}

//------------------------------------------------------------------------------

void AvatarManagerServer::constructStatics() {
	m_pDIAvatar = new DatabaseInterface(static_cast<DatabaseInterfaceParams&>(AvatarManagerServer::getDBParams()));
}

//------------------------------------------------------------------------------

void AvatarManagerServer::deleteStatics() {
	delete m_pDIAvatar;
}